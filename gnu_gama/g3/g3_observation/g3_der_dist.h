/*  
    GNU Gama -- adjustment of geodetic networks
    Copyright (C) 2003  Ales Cepek <cepek@fsv.cvut.cz>

    This file is part of the GNU Gama C++ library.
    
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
 *  $Id: g3_der_dist.h,v 1.1 2003/03/29 13:33:57 cepek Exp $
 */

#ifndef GNU_gama__g3_der_dist_h_gnugamag3der_disth___gnu_gama_g3der
#define GNU_gama__g3_der_dist_h_gnugamag3der_disth___gnu_gama_g3der


namespace GNU_gama {  namespace g3 {

  class Distance;

  class DistanceAnalyticalDerivative {
  public:
    
    virtual double analytical_derivative(Distance*) = 0;
  };
  
}}


#endif