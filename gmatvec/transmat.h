/*  
    C++ Matrix/Vector templates (GNU Gama / gMatVec 0.9.24)
    Copyright (C) 1999  Ales Cepek <cepek@gnu.org>

    This file is part of the gMatVec C++ Matrix/Vector template library.
    
    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
 *  $Id: transmat.h,v 1.13 2004/08/30 18:18:55 cepek Exp $
 *  http://www.gnu.org/software/gama/
 */

#ifndef gMatVec_TransMat__h_
#define gMatVec_TransMat__h_

#include <iostream>
#include <cstdarg>
#include <gmatvec/mat.h>
#include <gmatvec/vec.h>
#include <gmatvec/transvec.h>

namespace gMatVec {


template <typename Float, typename Exc> 
class TransMat : public MatBase<Float, Exc> {

public:

  typedef typename MatBase<Float, Exc>::iterator       iterator;
  typedef typename MatBase<Float, Exc>::const_iterator const_iterator;

  TransMat() {}
  TransMat(Index r, Index c) : MatBase<Float, Exc>(c, r, r*c) {}
  TransMat(const Mat<Float, Exc> &M) 
    :  MatBase<Float, Exc>(M.cols(), M.rows(), M)  {}

  Float& operator()(Index r, Index c) {
    Float *m = this->begin();
    return m[--c*this->rows() + --r];
  }
  Float  operator()(Index r, Index c) const {
    const Float *m = this->begin();
    return m[--c*this->rows() + --r];
  }

  void reset(Index r, Index c) {
    if (r != this->row_ || c != this->col_) {
      this->row_ = r; this->col_ = c; this->resize(r*c);
    }
  }

  TransMat operator*(Float f) const { 
    TransMat t(this->rows(), this->cols()); mul(f, t); return t; 
  }
  TransMat operator+(const TransMat& M) const { 
    if (this->rows() != M.rows() || this->cols() != M.cols())
      throw Exc(BadRank, "TransMat operator+(const TransMat& M) const");
    
    TransMat T(this->rows(), this->cols()); 
    add(M, T); 
    return T; 
  }
  TransMat operator-(const TransMat& M) const { 
    if (this->rows() != M.rows() || this->cols() != M.cols())
      throw Exc(BadRank, "TransMat operator-(const TransMat& M) const");
    
    TransMat T(this->rows(), this->cols()); 
    sub(M, T); 
    return T; 
  }

};


template <typename Float, typename Exc>
inline TransMat<Float, Exc> operator*(Float f, const TransMat<Float, Exc> &M) {
  return M*f;
}


template <typename Float, typename Exc>
Mat<Float, Exc>::Mat(const TransMat<Float, Exc>& M)
  : MatBase<Float, Exc>(M.rows(), M.cols(), M.rows()*M.cols()) 
{
  iterator p=this->begin();
  const Index R = M.rows();
  const Index C = M.cols();
  Index i, j;
  for (i=1; i<=R; i++)
    for (j=1; j<=C; j++, ++p)
      *p = M(i,j);
}


template <typename Float, typename Exc>
inline TransMat<Float, Exc> trans(const Mat<Float, Exc> &M) {
  return TransMat<Float, Exc>(M);
}


template <typename Float, typename Exc>
Mat<Float, Exc> trans(const TransMat<Float, Exc> &M) 
{
  Mat<Float, Exc> T(M.cols(), M.rows());
  typename Mat<Float, Exc>::iterator p=T.begin();
  const Index R = M.rows();
  const Index C = M.cols();
  Index i, j;
  for (j=1; j<=C; j++)
    for (i=1; i<=R; i++, ++p)
      *p = M(i,j);
  return T;
}


template <typename Float, typename Exc>
Mat<Float, Exc> 
operator+(const Mat<Float, Exc> &A, const TransMat<Float, Exc> &B) 
  {
    if (A.rows() != B.rows() || A.cols() != B.cols())
      throw Exc(BadRank, "Mat operator+(const Mat&, const TransMat&)");

    Mat<Float, Exc> T(B);
    typename Mat<Float, Exc>::iterator t=T.begin();
    typename Mat<Float, Exc>::const_iterator b=A.begin();
    typename Mat<Float, Exc>::const_iterator e=A.end();

    while (b != e)  *t++ += *b++;

    return T; 
  }


template <typename Float, typename Exc>
inline Mat<Float, Exc> 
operator-(const Mat<Float, Exc> &A, const TransMat<Float, Exc> &B) 
  { 
    if (A.rows() != B.rows() || A.cols() != B.cols())
      throw Exc(BadRank, "Mat operator-(const Mat&, const TransMat&)");

    Mat<Float, Exc> T(B);
    typename Mat<Float, Exc>::iterator t=T.begin();
    typename Mat<Float, Exc>::const_iterator b=A.begin();
    typename Mat<Float, Exc>::const_iterator e=A.end();

    while (b != e)  *t = *b++ - *t++;

    return T; 
  }


template <typename Float, typename Exc>
inline Mat<Float, Exc> 
operator+(const TransMat<Float, Exc> &A, const Mat<Float, Exc> &B) 
  {  
    if (A.rows() != B.rows() || A.cols() != B.cols())
      throw Exc(BadRank, "Mat operator+(const TransMat&, const Mat&)");

    Mat<Float, Exc> T(A);
    typename Mat<Float, Exc>::iterator t=T.begin();
    typename Mat<Float, Exc>::const_iterator b=B.begin();
    typename Mat<Float, Exc>::const_iterator e=B.end();

    while (b != e)  *t++ += *b++;

    return T; 
  }


template <typename Float, typename Exc>
inline Mat<Float, Exc> 
operator-(const TransMat<Float, Exc> &A, const Mat<Float, Exc> &B) 
  { 
    if (A.rows() != B.rows() || A.cols() != B.cols())
      throw Exc(BadRank, "Mat operator-(const TransMat&, const Mat&)");

    Mat<Float, Exc> T(A);
    typename Mat<Float, Exc>::iterator t=T.begin();
    typename Mat<Float, Exc>::const_iterator b=B.begin();
    typename Mat<Float, Exc>::const_iterator e=B.end();

    while (b != e)  *t++ -= *b++;

    return T; 
  }


template <typename Float, typename Exc>
Vec<Float, Exc> 
operator*(const TransMat<Float, Exc> &A, const Vec<Float, Exc> &b)
  {
    if (A.cols() != b.dim())
      throw Exc(BadRank, "Vec operator*(const TransMat&, const Vec&)");

    Vec<Float, Exc> t(A.rows());
    typename Vec<Float, Exc>::iterator ti = t.begin();
    typename Vec<Float, Exc>::const_iterator bb = b.begin();
    typename Vec<Float, Exc>::const_iterator bi;
    typename TransMat<Float, Exc>::const_iterator ab = A.begin();
    typename TransMat<Float, Exc>::const_iterator ai;
    Float s;
    for (Index i=1; i<=A.rows(); i++)
      {
        s = 0;
        bi = bb;
        ai = ab;
        for (Index j=1; j<=A.cols(); j++, ai += A.rows()) 
          s += *ai * *bi++;
        *ti++ = s;
        ab++;
      }

    return t;
  }


template <typename Float, typename Exc>
TransVec<Float, Exc> 
operator*(const Vec<Float, Exc> &b, const TransMat<Float, Exc> &A)
  {
    if (A.rows() != b.dim())
      throw Exc(BadRank, "TransVec operator*(const TransMat&, const Vec&)");

    TransVec<Float, Exc> t(A.rows());
    typename TransVec<Float, Exc>::iterator ti = t.begin();
    typename Vec<Float, Exc>::const_iterator bb = b.begin();
    typename Vec<Float, Exc>::const_iterator bi;
    typename TransMat<Float, Exc>::const_iterator ab = A.begin();
    typename TransMat<Float, Exc>::const_iterator ai;
    const Index a_cols = A.cols();
    Float s;
    for (Index i=1; i<=A.rows(); i++)
      {
        s = 0;
        bi = bb;
        ai = ab;
        for (Index j=1; j<=a_cols; j++, ai += a_cols) 
          s += *ai * *bi++;
        *ti++ = s;
        ab++;
      }

    return t;
  }


template <typename Float, typename Exc>
Mat<Float, Exc>
operator*(const TransMat<Float, Exc> &A, const Mat<Float, Exc> &B)
  {
    if (A.cols() != B.rows())
      throw Exc(BadRank, "Mat operator*(const TransMat&, const Mat&)");

    Mat<Float, Exc> C(A.rows(), B.cols());
    typename Mat<Float, Exc>::iterator c = C.begin();
    typename TransMat<Float, Exc>::const_iterator ab = A.begin();
    typename TransMat<Float, Exc>::const_iterator a;
    typename Mat<Float, Exc>::const_iterator bb = B.begin();
    typename Mat<Float, Exc>::const_iterator b;
    Float s;
    
    for (Index i=1; i<=C.rows(); i++, ab++)
      for (Index j=0; j<C.cols(); j++)
        {
          s = 0;
          a = ab;
          b = bb + j;
          for (Index k=1; k<=A.cols(); k++, b += B.cols(), a += A.rows())
            s += *a * *b;
          *c++ = s;
        }

    return C;
  }


template <typename Float, typename Exc>
Mat<Float, Exc>
operator*(const Mat<Float, Exc> &A, const TransMat<Float, Exc> &B)
  {
    if (A.cols() != B.rows())
      throw Exc(BadRank, "Mat operator*(const Mat&, const TransMat&)");

    Mat<Float, Exc> C(A.rows(), B.cols());
    typename Mat<Float, Exc>::iterator c = C.begin();
    typename Mat<Float, Exc>::const_iterator ab = A.begin();
    typename Mat<Float, Exc>::const_iterator a;
    typename TransMat<Float, Exc>::const_iterator bb = B.begin();
    typename TransMat<Float, Exc>::const_iterator b;
    Float s;

    for (Index i=1; i<=C.rows(); i++, ab += A.cols())
      for (Index j=0; j<C.cols(); j++)
        {
          s = 0;
          a = ab;
          b = bb + j*B.rows();
          for (Index k=1; k<=A.cols(); k++, b++)
            s += *a++ * *b;
          *c++ = s;
        }

    return C;
  }


template <typename Float, typename Exc>
Mat<Float, Exc>
operator*(const TransMat<Float, Exc> &A, const TransMat<Float, Exc> &B)
  {
    if (A.cols() != B.rows())
      throw Exc(BadRank, "Mat operator*(const TransMat&, const TransMat&)");

    Mat<Float, Exc> C(A.rows(), B.cols());
    typename Mat<Float, Exc>::iterator c = C.begin();
    typename TransMat<Float, Exc>::const_iterator ab = A.begin();
    typename TransMat<Float, Exc>::const_iterator a;
    typename TransMat<Float, Exc>::const_iterator bb = B.begin();
    typename TransMat<Float, Exc>::const_iterator b;
    Float s;
    
    for (Index i=1; i<=C.rows(); i++, ab++)
      for (Index j=0; j<C.cols(); j++)
        {
          s = 0;
          a = ab;
          b = bb + j*B.cols();
          for (Index k=1; k<=A.cols(); k++, a += A.rows(), b++)
            s += *a * *b;
          *c++ = s;
        }

    return C;
  }


}   // namespace gMatVec

#endif
