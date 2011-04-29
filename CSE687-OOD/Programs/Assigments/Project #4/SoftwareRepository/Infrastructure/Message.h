#ifndef MESSAGE_H
#define MESSAGE_H
/////////////////////////////////////////////////////////////////////////
//  Message.h    -  Message class and message type enum   		   //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 2010                               //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #4	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////
/*
   Module Operations:
   ==================
   This module provide Message class and MsgType class.
  
   The MsgType class provide enum type of message for Message class,
   it also offers two helper functions for covert between enum and string

   Message gives interface to know the type of xml format message 
  
   Public Interface:
   =================
   enum Value
   {
	   Login,	//user login
	   Dependency,	//request all dependencies
	   Package,	//request package info
	   File,	//request files
	   Checkin,	//upload files
	   Commit,	//commit files to close
	   Warning, //warning message

	   Unknown
   };

   MsgType::StringToEnum(tagName);
   MsgType::EnumToString(MsgType::Login);
   Message msg();
   msg.SetMessage(xml);
   cout<<msg.Type()<<endl;
   cout<<msg.ToString();


   Build Process:
   ==============
   Required Files:
	xmlTran.h, xmlTran.cpp, XmlDoc.h, XmlDoc.cpp
	Message.h, Message.cpp

*/
#include <string>

#include "XmlDoc.h"

namespace Ider
{
	struct MsgType
	{
		enum Value
		{
			Login,
			Dependency,
			Package,
			File,
			Checkin,
			Commit,
			Warning,

			Unknown
		};
		static strVal EnumToString(MsgType::Value type);
		static Value StringToEnum(conStrRef type);
	};

	class Message
	{
	public:
		Message(){ type = MsgType::Unknown;}
		Message(conStrRef xml);

		operator std::string(){return doc.ToString();}
		MsgType::Value Type()const{return type;}
		XmlDoc Doc()const{return doc;}
		virtual void SetMessage(conStrRef xml);
		strVal ToString()const{return doc.ToString();}
	protected:
		virtual	void  SetType(strVal tagName);
		XmlDoc doc;
		MsgType::Value type;
	};
}

#endif