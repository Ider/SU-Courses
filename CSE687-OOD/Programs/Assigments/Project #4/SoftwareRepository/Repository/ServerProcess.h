/////////////////////////////////////////////////////////////////////////
//  ServerProcess.cpp   -  Server side thread process   		   //
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
   This module provides two classes for message thread process.
   These processes listen to client, and receive the message or file
   from client. They also use MessageHandler to analyze the message,
   and post back a corresponding message.

   Thread class must inherit from Thread_Processing<typename T> template
   class, where the template parameter is itself, then thread class implement
   run() method, so it will be operating on other thread.

   The module also provide a Class for wrap a globe MessageHanlder instant.
   this instant will be referenced by tread class.

   Public Interface:
   =================
	

*/

#ifndef SERVER_PROCESS_H
#define SERVER_PROCESS_H

#include "..\Foundation\Communicator.h"
#include "ServerMessageHandler.h"

class ServerMessageHandlerInstant
{
public:
	static MessageHandler& Value()
	{
		return instant;
	}
private:
	static MessageHandler instant;
};

//Server side message process thread class
class ServerMessage_Proc : public Thread_Processing<ServerMessage_Proc>
{
public:
	ServerMessage_Proc(IMsgHandler* pMsgHandler) 
		: _pMsgHandler(pMsgHandler) 
		,mh(ServerMessageHandlerInstant::Value())
	{}
	//implement interface
 	void run();
private:

 	void PostFile(Ider::Message msg);

	IMsgHandler* _pMsgHandler;
	MessageHandler& mh;
};

//Server side file process thread class
class ServerFile_Proc : public Thread_Processing<ServerFile_Proc>
{
public:
	ServerFile_Proc(IFileHandler* pFileHandler) 
		: _pFileHandler(pFileHandler) 
		,mh(ServerMessageHandlerInstant::Value())
	{}

	//implement interface
 	void run();
private:

	IFileHandler* _pFileHandler;
	MessageHandler& mh;
};


#endif