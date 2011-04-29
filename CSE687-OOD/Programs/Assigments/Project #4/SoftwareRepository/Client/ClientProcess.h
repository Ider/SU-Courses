#ifndef CLIENT_PROCESS_H
#define CLIENT_PROCESS_H

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