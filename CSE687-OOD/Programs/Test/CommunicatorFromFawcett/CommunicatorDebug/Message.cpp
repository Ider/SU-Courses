/////////////////////////////////////////////////////////////////////
// Message.cpp  - Defines EndPoints and Messages                   //
// ver 1.1                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Dimension T7400, Win 7 Pro                  //
// Application:   Utility for CSE687 projects                      //
// Author:        Jim Fawcett, Syracuse University, CST 4-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include "Message.h"
#include "../XmlDocument/XmlDocument.h"
#include <iostream>
#include <sstream>
using namespace XmlProcessing;

/////////////////////////////////////////////////////////////
// converters to and from string

template <typename T>
std::string ToString(T t)
{
  std::ostringstream temp;
  temp << t;
  return temp.str();
}

template <typename T>
T FromString(const std::string& s)
{
  T t;
  std::istringstream temp(s);
  temp >> t;
  return t;
}
///////////////////////////////////////////////////////////////
// Manage endpoints

EndPoint::EndPoint(const std::string& address, long port)
{
  ep = address + ":" + ::ToString(port); 
}

EndPoint::EndPoint(const std::string& eps) : ep(eps) {}

std::string EndPoint::address()
{
  size_t pos = ep.find(":");
  return ep.substr(0,pos);
}
long EndPoint::port()
{
  size_t pos = ep.find(":");
  std::string pnum = ep.substr(pos+1);
  return FromString<long>(pnum);
}

std::string& EndPoint::ToString()
{
  return ep;
}

//std::string IEndPoint::MakeEndPoint(const std::string& ipaddr, long port)
//{
//  EndPoint ep(ipaddr,port);
//  return ep.ToString();
//}

///////////////////////////////////////////////////////////////
// Build Messages

Message::Message(const std::string& text) 
       : body_(text), returnAddr_(EndPoint("127.0.0.1",8000)), type_(Message::text) {}

Message::Message(const std::string& body, EndPoint returnAddr, MsgType type)
       : body_(body), returnAddr_(returnAddr), type_(type) {}

Message::Message(const Message& msg) 
       : body_(msg.body_), returnAddr_(msg.returnAddr_), type_(msg.type_) {}

std::string& Message::body() { return body_; }
  
EndPoint& Message::returnAddress() { return returnAddr_; }
  
Message::MsgType& Message::getMsgType() { return type_; }

std::string& Message::getEndPoint() { return returnAddr_.ToString(); }

//----< return string form of Message type >-----------------------------

std::string Message::TypeToString()
{
  switch(type_)
  {
  case text:
    return "text";
  case file:
    return "file";
  }
  return "unknown type";
}
//----< serialize message to string >------------------------------------

std::string Message::ToString()
{
  std::string temp = "<msg>";
  temp += std::string("<type>") + TypeToString() + "</type>";
  temp += std::string("<rAddress>") + returnAddress().ToString() + "</rAddress>";
  temp += std::string("<body>") + body() + "</body></msg>";
  return temp;
}
//----< remove quotes from quoted string >-------------------------------

std::string Message::trimQuotes(const std::string& s)
{
  if(s.size() > 0 && s[0] == '"')
    return s.substr(1,s.size()-2);
  if(s.size() > 0 && s[0] == '\'')
    return s.substr(1,s.size()-2);
  return s;
}
//----< deserialize message string into Message instance >---------------

Message Message::FromString(const std::string& xml)
{
  std::vector<IXmlNode*> children;
  Message msg("");
  std::string temp;
  XmlDocument doc;
  doc.verbose() = false;
  doc.loadString(xml);
  IXmlNode* pNode = doc.findElement("type",XmlDocument::tag);
  if(pNode)
  {
    children = pNode->getChildren();
    if(children[0]->value() =="text")
      msg.getMsgType() = Message::text;
    else
      msg.getMsgType() = Message::file;
  }
  pNode = doc.findElement("rAddress",XmlDocument::tag);
  if(pNode)
  {
    children = pNode->getChildren();
    msg.returnAddress() = EndPoint(children[0]->value());
  }
  pNode = doc.findElement("body",XmlDocument::tag);
  if(pNode)
  {
    children = pNode->getChildren();
    msg.body() = trimQuotes(children[0]->value());
  }
  return msg;
}

//IMessage* IMessage::MakeMessage(const std::string& EndPoint, MsgType type, const std::string& body)
//{
//  return new Message(body, EndPoint, type);
//}

EndPoint testEndPoint()
{
  EndPoint ep("127.0.0.1", 8000);
  std::cout << "\n  EndPoint = " << ep.ToString();
  std::cout << "\n  Address  = " << ep.address();
  std::cout << "\n  Port     = " << ep.port();
  return ep;
}

Message testMessage(EndPoint ep)
{
  Message msg("This is a message", ep, Message::text);
  std::cout << "\n  Message body = " << msg.body();
  std::cout << "\n  Message return address = " << msg.returnAddress().ToString();
  std::cout << "\n  Message type = " << msg.TypeToString();
  std::cout << "\n";
  std::cout << "\n  Message:";
  std::cout << "\n  " << msg.ToString();
  return msg;
}
//----< test stub >------------------------------------------------------

#ifdef TEST_MESSAGE

void main()
{
  std::cout << "\n  Demonstrating EndPoint and Message Operations";
  std::cout << "\n ===============================================\n";

  EndPoint ep = testEndPoint();
  std::cout << "\n";

  Message msg = testMessage(ep);

  std::cout << "\n\n";
}

#endif
