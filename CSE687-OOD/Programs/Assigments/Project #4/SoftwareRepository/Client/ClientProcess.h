#ifndef CLIENT_PROCESS_H

#define CLIENT_PROCESS_H

#include "..\Foundation\Communicator.h"
#include "ClientMessageHandler.h"

#include "UserInterface.h"

#include <conio.h>

/////////////////////////////////////////////////////////////////////
// Thread Proc classes for Client side

class ClientMessage_Proc : public Thread_Processing<ClientMessage_Proc>
{
public:
	ClientMessage_Proc(IMsgHandler* pMsgHandler) : _pMsgHandler(pMsgHandler) {}
	void run()
	{
		GLock<1> lock;
		std::string msg;
		lock.lock();
		BQueue<std::string>* pBQ = _pMsgHandler->getQueue();
		ICommunicator* pComm = _pMsgHandler->getCommunicator();
		EndPoint remoteEp = _pMsgHandler->getEndPoint();
		lock.unlock();
		///////////////////////////////////////////////////////
		// enter your server code here
		while(true)
		{
			sout << locker << "\n  sender received message: " 
				<< (msg = pBQ->deQ()).c_str() << unlocker;
			if(msg == "quit")
				break;
		}
		// end of your code
		///////////////////////////////////////////////////////
	}
private:
	IMsgHandler* _pMsgHandler;
};

class ClientFile_Proc : public Thread_Processing<ClientFile_Proc>
{
public:
	ClientFile_Proc(IFileHandler* pFileHandler) : _pFileHandler(pFileHandler) {}
	void run()
	{
		GLock<1> lock;
		std::string msg;
		lock.lock();
		BQueue<std::string>* pBQ = _pFileHandler->getQueue();
		ICommunicator* pComm = _pFileHandler->getCommunicator();
		EndPoint remoteEp = _pFileHandler->getEndPoint();
		lock.unlock();
		///////////////////////////////////////////////////////
		// enter your server code here
		while(true)
		{
			sout << locker << "\n  sender received file: " 
				<< (msg = pBQ->deQ()).c_str() << unlocker;
			if(msg == "quit")
				break;
		}
		// end of your code
		///////////////////////////////////////////////////////
	}
private:
	IFileHandler* _pFileHandler;
};


#endif