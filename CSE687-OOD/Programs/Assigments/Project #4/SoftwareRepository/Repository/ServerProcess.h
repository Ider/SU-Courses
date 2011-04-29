
#ifndef SERVER_PROCESS_H
#define SERVER_PROCESS_H

#include "..\Foundation\Communicator.h"
#include "ServerMessageHandler.h"

static MessageHandler ServerMessageHandler;

class ServerMessage_Proc : public Thread_Processing<ServerMessage_Proc>
{
public:
	ServerMessage_Proc(IMsgHandler* pMsgHandler) 
		: _pMsgHandler(pMsgHandler) 
		,mh(::ServerMessageHandler)
	{}
 	void run();
private:

 	void PostFile(Ider::Message msg);

	IMsgHandler* _pMsgHandler;
	MessageHandler& mh;
};

class ServerFile_Proc : public Thread_Processing<ServerFile_Proc>
{
public:
	ServerFile_Proc(IFileHandler* pFileHandler) 
		: _pFileHandler(pFileHandler) 
		,mh(::ServerMessageHandler)
	{}

 	void run();
private:

	IFileHandler* _pFileHandler;
	MessageHandler& mh;
};


#endif