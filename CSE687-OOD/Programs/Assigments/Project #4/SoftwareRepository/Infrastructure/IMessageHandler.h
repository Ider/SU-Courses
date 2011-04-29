#ifndef IMESSAGE_HANDLER_H
#define IMESSAGE_HANDLER_H
/////////////////////////////////////////////////////////////////////////
//  IMessageHandler.cpp    -  provide a interface for message Hanlder  //
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
   This module provides a interface IMessageHandler.

   The interface only have two methods:
	   ReceiveMessage: receive a message
	   MessageForseding: generate a specific type message for sending

   Public Interface:
   =================
   virtual void ReceiveMessage(conStrRef message )=0;
   virtual Message MessageForSending(MsgType::Value type)=0;
  
   Build Process:
   ==============
   Required Files:
     Message.h, Message.cpp, IMessageHandler.h

   
*/



#include "Message.h"

namespace Ider
{
	class IMessageHandler
	{
	public:
		virtual void ReceiveMessage(conStrRef message )=0;
		virtual Message MessageForSending(MsgType::Value type)=0;
		virtual ~IMessageHandler(){}
	};

}


#endif