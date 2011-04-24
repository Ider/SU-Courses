
#include "..\Foundation\Communicator.h"
#include "ServerMessageHandler.h"
#include <conio.h>

#ifdef MAIN_TEST

class MsgReceiver_Proc : public Thread_Processing<MsgReceiver_Proc>
{
public:
	MsgReceiver_Proc(IMsgHandler* pMsgHandler) : _pMsgHandler(pMsgHandler) {}
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
		// insert your server processing here
		while(true)
		{
			sout << locker << "\n  receiver processing message: " 
				<< (msg = pBQ->deQ()).c_str() << unlocker;
			lock.lock();
			EndPoint remoteEp = _pMsgHandler->getEndPoint();
			if(pComm->connect(remoteEp.getIP(), remoteEp.getPort()))
			{
				Message message(msg);
				mh.ReceiveMessage(msg);
				message = mh.MessageForSending(MsgType::Unknown);

				pComm->postMessage(message.ToString());
				pComm->disconnect();
			}
			else
				sout << "\n  failed to connect";
			lock.unlock();

			if(msg == "quit")
				break;
		}
		// end of your code
		///////////////////////////////////////////////////////
	}
private:
	IMsgHandler* _pMsgHandler;
	MessageHandler mh;
};

class FileReceiver_Proc : public Thread_Processing<FileReceiver_Proc>
{
public:
	FileReceiver_Proc(IFileHandler* pFileHandler) : _pFileHandler(pFileHandler) {}
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
		// insert your server code here
		while(true)
		{
			sout << locker << "\n  receiver processing file: " << (msg = pBQ->deQ()).c_str() << unlocker;
			lock.lock();
			EndPoint remoteEp = _pFileHandler->getEndPoint();
			if(pComm->connect(remoteEp.getIP(), remoteEp.getPort()))
			{
				pComm->postMessage(std::string("got file\n"));
				pComm->disconnect();
			}
			else
				sout << "\n  failed to connect";
			lock.unlock();

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
	sout << locker << "\n  Testing Socket Communicator Server"
		<< "\n =============================\n" << unlocker;

	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false); 

	//// Create the main window and run it
	// Application::Run(gcnew SocketComm::DemoForm());

	try
	{
		EndPoint rep("127.0.0.1",2048);

		// MsgReceiver_Proc is your receiver's server message handling
		// FileReceiver_Proc is your receiver's server file handling
		Communicator rcvr(rep);
		MsgHandler<MsgReceiver_Proc> rMsgHandler;
		rMsgHandler.setCommunicator(&rcvr);
		rcvr.attachMsgHandler(&rMsgHandler);
		FileHandler<FileReceiver_Proc> rFileHandler;
		rFileHandler.setFileDestination(".\\FilePostTest\\Receiver\\");
		rFileHandler.setCommunicator(&rcvr);
		rcvr.attachFileHandler(&rFileHandler);
		rcvr.listen();

		_getche();

	}
	catch(std::exception& ex)
	{
		sout << locker << "\n  " << ex.what() << "\n\n" << unlocker;
	}
}


#endif
