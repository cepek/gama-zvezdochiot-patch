/*  
    Geodesy and Mapping C++ Library (GNU GaMa / GaMaLib)
    Copyright (C) 2002  Ales Cepek <cepek@fsv.cvut.cz>

    This file is part of the GNU GaMa / GaMaLib C++ Library.
    
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

#include <gamalib/xml/baseparser.h>
#include <gamalib/xml/encoding.h>

using namespace std;
using namespace GaMaLib;


// ===========================================================================

namespace {
  extern "C" {
    
    void characterDataHandler(void *userData, const char* s, int len)
    {
      using namespace GaMaLib;
      BaseParser* gexp = static_cast<BaseParser*>(userData);
      
      gexp->characterDataHandler(s, len);
    }      
    
    void startElement(void *userData, const char *cname, const char **atts)
    {
      using namespace GaMaLib;
      BaseParser* gexp = static_cast<BaseParser*>(userData);

      gexp->startElement(cname, atts);
    }

    void endElement(void *userData, const char *cname)
    {
      using namespace GaMaLib;
      BaseParser* gexp = static_cast<BaseParser*>(userData);

      gexp->endElement(cname);
    }

  }   // extern "C" 
}     // unnamed namespace 

// ===========================================================================



const int BaseParser::state_error = 0; 

BaseParser::BaseParser()
{
  parser  = XML_ParserCreate(0);
 
  XML_SetUserData              (parser, this);
  XML_SetElementHandler        (parser, ::startElement, ::endElement);
  XML_SetCharacterDataHandler  (parser, ::characterDataHandler);
  XML_SetUnknownEncodingHandler(parser, UnknownEncodingHandler, 0);
}

BaseParser::~BaseParser()
{
  XML_ParserFree(parser); 
}

void BaseParser::xml_parse(const char *s, int len, int  isFinal) 
{ 
  int err = XML_Parse(parser, s, len, isFinal);
  if (err == 0)
    {
      // fatal error
      
      errString=std::string(XML_ErrorString(XML_GetErrorCode(parser)));
      errCode  =XML_GetErrorCode(parser);
      errLineNumber = XML_GetCurrentLineNumber(parser);
      
      throw ParserException(errString, errLineNumber);
    }
  
  if (state == state_error)
    {
      errCode = -1;   
      // errLineNumber is set by function  error("...");    
      throw ParserException(errString, errLineNumber);
    }
}


bool BaseParser::toDouble(const std::string& s, double& d) const
{
  using namespace std;        // Visual C++ doesn't know std::atof ???
  
  if (IsFloat(s))
    {
      d = atof(s.c_str());
      return true;
    }
  else
    return false;
}



bool BaseParser::toIndex(const std::string& s, Index& index) const
{
  for (std::string::const_iterator i=s.begin(); i!=s.end(); ++i)
    if (!isspace(*i) && !isdigit(*i))
      return false;
  
  double d;
  if (toDouble(s, d))
    {
      index = static_cast<Index>(d);
      return true;
    }
  else
    return false;
}

int BaseParser::error(const char* text)
    {
      // store only the first detected error
      if(errCode) return 1;
      
      errString = std::string(text);
      errCode   = -1;
      errLineNumber = XML_GetCurrentLineNumber(parser);
      state = state_error;
      return 1;
    }
    


