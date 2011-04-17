/////////////////////////////////////////////////////////////////////
// MsgHandler.cpp - Processing for Received Messages               //
// ver 1.0                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Precision 7500, Windows Vista, SP 1.0       //
// Application:   Utility for CSE687 Project #4                    //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include "MsgHandler.h"

//----< construct EndPoint >-----------------------------------------

EndPoint::EndPoint(const std::string& ip, int port)
{
  std::ostringstream temp;
  temp << ip << ':' << port;
  _ipport = temp.str();
}
//----< return ip address of EndPoint >------------------------------

std::string EndPoint::getIP()
{
  size_t pos = _ipport.find(':');
  return _ipport.substr(0,pos);
}
//----< return port number of EndPoint >-----------------------------

int EndPoint::getPort()
{
  size_t pos = _ipport.find(':') + 1;
  std::string temp = _ipport.substr(pos,_ipport.size());
  std::istringstream portStr(temp);
  int port;
  portStr >> port;
  return port;
}
