#ifndef CLIENT_PROCESS_H
#define CLIENT_PROCESS_H
/////////////////////////////////////////////////////////////////////////
//  ClientProcess.h    -  Thread Process classes for Client side       //
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
   This module provides two thread process for listening to get message or 
   files from server.

   The class must inherit from template Thread_Processing<typename T>
   where the typename should be itself.

   Public Interface:
   =================
   ClientMessage_Proc.run()
   ClientFile_Proc.run()

   Build Process:
   ==============
   Required Files:
     ClientMessageHandler.h, ClientMessageHandler.cpp, Communicator.h

*/

#include "..\Foundation\Communicator.h"
#include "ClientMessageHandler.h"
#include "UserInterface.h"


extern Ider::IMessageHandler* FormMessageHanlder;

/////////////////////////////////////////////////////////////////////
// Thread Proc classes for Client side

class ClientMessage_Proc : public Thread_Processing<ClientMessage_Proc>
{
public:
	ClientMessage_Proc(IMsgHandler* pMsgHandler) 
		: _pMsgHandler(pMsgHandler) {}
	//Implement interface Thread_Processing<ClientMessage_Proc>
	void run();
private:
	IMsgHandler* _pMsgHandler;
};

class ClientFile_Proc : public Thread_Processing<ClientFile_Proc>
{
public:
	ClientFile_Proc(IFileHandler* pFileHandler) 
		: _pFileHandler(pFileHandler) {}
	//Implement interface Thread_Processing<ClientFile_Proc>
	void run();
private:
	IFileHandler* _pFileHandler;
};


#endif