
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

class ServerMessage_Proc : public Thread_Processing<ServerMessage_Proc>
{
public:
	ServerMessage_Proc(IMsgHandler* pMsgHandler) 
		: _pMsgHandler(pMsgHandler) 
		,mh(ServerMessageHandlerInstant::Value())
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
		,mh(ServerMessageHandlerInstant::Value())
	{}

 	void run();
private:

	IFileHandler* _pFileHandler;
	MessageHandler& mh;
};


#endif