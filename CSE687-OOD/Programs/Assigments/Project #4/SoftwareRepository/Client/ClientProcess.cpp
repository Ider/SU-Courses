
#include "..\Foundation\Communicator.h"
#include "ClientMessageHandler.h"

#include "UserInterface.h"
#include <conio.h>

Ider::IMessageHandler* FormMessageHanlder;

void ClientMessage_Proc::run()
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
		msg = pBQ->deQ();
		sout << locker << "\n\n  Client received message: \n" 
			<< msg << unlocker;

		FormMessageHanlder->ReceiveMessage(msg);
	}
	// end of your code
	///////////////////////////////////////////////////////
}

void ClientFile_Proc::run()
{
	GLock<1> lock;
	std::string msg;
	lock.lock();
	BQueue<std::string>* pBQ = _pFileHandler->getQueue();
	//ICommunicator* pComm = _pFileHandler->getCommunicator();
	//EndPoint remoteEp = _pFileHandler->getEndPoint();
	lock.unlock();

	while(true)
	{
		sout << locker << "\n  Client received file: " 
			<< (msg = pBQ->deQ()).c_str() << unlocker;
	}
}


#ifdef MAIN_TEST

/////////////////////////////////////////////////////////////////////
// Thread Proc classes for sender

class MsgSender_Proc : public Thread_Processing<MsgSender_Proc>
{
public:
	MsgSender_Proc(IMsgHandler* pMsgHandler) : _pMsgHandler(pMsgHandler) {}
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

class FileSender_Proc : public Thread_Processing<FileSender_Proc>
{
public:
	FileSender_Proc(IFileHandler* pFileHandler) : _pFileHandler(pFileHandler) {}
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


void main()
{
	sout << locker << "\n  Testing Socket Communicator Client"
		<< "\n ========================================\n" << unlocker;

	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false); 

	//// Create the main window and run it
	// Application::Run(gcnew SocketComm::DemoForm());

	try
	{
		EndPoint rep("127.0.0.1",2048);
		EndPoint sep("127.0.0.1",2049);

		// MsgSender_Proc is your sender's server message handling
		//   If you don't have sender server file handling don't 
		//   attach a file handler
		Communicator sndr(sep);
		sndr.setFileSource(".\\FilePostTest\\Sender\\");
		MsgHandler<MsgSender_Proc> smsgHandler;
		sndr.attachMsgHandler(&smsgHandler);
		sndr.listen();

		// The MsgReceiver_Proc and FileReceiver_Proc
		// should connect when they have a reply, so
		// don't connect the receiver - that's done
		// by your server code (see above)

		if(!sndr.connect("127.0.0.1",2048))
		{
			sout << "\n  failed to connect sndr\n\n";
			return;
		}

		sout<<"  start posting\n";

		// 		sndr.postMessage("first message");
		// 		sndr.postMessage("second message");
		// 		sndr.postMessage("third and longer message");
		// 		sndr.postMessage("fourth and still longer and most verbose message");
		// 		sndr.postFile("test.txt");
		// 		sndr.postFile("Project #4 Analysis.docx");
		// 		sndr.postFile("FormWithCppThread.zip");
		//sndr.postFile("notepad.exe");
		//sndr.postMessage("quit");

		MessageHandler mh;
		Message msg = mh.MessageForSending(MsgType::Dependency);

		sndr.postMessage(msg.ToString());

		_getche();


		sout << locker << "\n  Socket connection count = " 
			<< sndr.getSocketConnectionCount() << unlocker;

		sout << "\n\n  press key to exit:  ";
		sout.flush();
		sout << "\n\n";
		//    rcvr.disconnect();
		sndr.disconnect();

	}
	catch(std::exception& ex)
	{
		sout << locker << "\n  " << ex.what() << "\n\n" << unlocker;
	}
}

#endif
