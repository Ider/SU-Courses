#ifndef MESSAGE_H
#define MESSAGE_H
/////////////////////////////////////////////////////////////////////
// Message.h   -  Defines EndPoints and Messages                   //
// ver 1.1                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Dimension T7400, Win 7 Pro                  //
// Application:   Utility for CSE687 projects                      //
// Author:        Jim Fawcett, Syracuse University, CST 4-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This package provides a Message class.  Its function is to build
  and parse XML messages.  Each message has a type, return address,
  and a text body.

  Build Process:
  ==============
  Required files
    - Message.h, Message.cpp, XmlDocument.h, XmlDocument.cpp,
      XmlElementParts.h, XmlElementParts.cpp, XmlNodes.h, XmlNodes.cpp,
      MTree.h, MTree.cpp, Tokenizer.h, Tokenizer.cpp
  Build commands (either one)
    - devenv XmlProcessing.sln
    - cl /EHsc Message.cpp, XmlDocument.cpp XmlElementParts.cpp XmlNodes.cpp Tokenizer.cpp

  Maintenance History:
  ====================
  ver 1.1 : 06 Apr 11
  - added these comments
  ver 1.0 : 25 Apr 10
  - first release
*/

#include <string>

/////////////////////////////////////////////////////////////////////////
// Manage addresses in the form 127.0.0.1:8000

class EndPoint //: public IEndPoint
{
public:
  EndPoint(const std::string& address, long port);
  EndPoint(const std::string& eps);
  std::string address();
  long port();
  std::string& ToString();
private:
  std::string ep;
};

/////////////////////////////////////////////////////////////////////////
// Create, serialize, and deserialize Message instances

class Message //: public IMessage
{
public:
  enum MsgType { text, file };
  Message(const std::string& text = "");
  Message(const std::string& body, EndPoint ep, MsgType type);
  Message(const Message& msg);
  std::string& getEndPoint();
  MsgType&  getMsgType();
  std::string& body();
  EndPoint& returnAddress();
  std::string TypeToString();
  std::string ToString();
  static Message FromString(const std::string& xml);
private:
  static std::string trimQuotes(const std::string& s);
  EndPoint returnAddr_;
  std::string body_;
  MsgType type_;
};

#endif
