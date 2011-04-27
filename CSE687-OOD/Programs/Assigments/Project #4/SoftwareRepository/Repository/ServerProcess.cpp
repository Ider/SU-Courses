
#include "..\Foundation\Communicator.h"
#include "ServerMessageHandler.h"
#include <conio.h>
#include <vector>
using namespace std;
using namespace Ider;

#ifdef MAIN_TEST
#endif

static MessageHandler ServerMessageHandler;

class MsgReceiver_Proc : public Thread_Processing<MsgReceiver_Proc>
{
public:
	MsgReceiver_Proc(IMsgHandler* pMsgHandler) : _pMsgHandler(pMsgHandler) 
	,mh(::ServerMessageHandler){}
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
			sout << locker << "\n  Server processing message: " 
				<< (msg = pBQ->deQ()).c_str() << unlocker;
			lock.lock();
			EndPoint remoteEp = _pMsgHandler->getEndPoint();
			if(pComm->connect(remoteEp.getIP(), remoteEp.getPort()))
			{
				Message receivedMsg(msg);//received me
				
				Message msgToSend = mh.RespondToMessage(receivedMsg,remoteEp);

				if (receivedMsg.Type() ==  MsgType::File
					&& msgToSend.Type()== MsgType::File)
					PostFile(msgToSend);
				else
					pComm->postMessage(msgToSend);

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

	void PostFile(Message msg)
	{
		ICommunicator* pComm = _pMsgHandler->getCommunicator();
		XmlDoc doc = msg.Doc();
		vector<XmlDoc> names = doc.Children("Name");
		strVal name;
		strVal loaded;
		strVal unload;
		strVal info;
		strVal prefix="\n  ";

		for (size_t i=0; i<names.size(); ++i)
		{
			name = names[i].InnerText();
			try
			{
				
				pComm->postFile(name+".h");
				loaded+=prefix+name+".h";
			}
			catch(std::exception ex)
			{unload+=prefix+name+".h";}

			try
			{
				pComm->postFile(name+".cpp");
				loaded+=prefix+name+".cpp";
			}
			catch(std::exception ex)
			{unload+=prefix+name+".cpp";}
		}

		if (loaded.size()>0)
			info += "Files loaded:"+loaded;
		if (unload.size()>0)
			info += "\nFiles not in repository:"+unload;
		if (info.size()>0)pComm->postMessage(mh.WarningMessage(info));
	}

	IMsgHandler* _pMsgHandler;
	MessageHandler& mh;
};

class FileReceiver_Proc : public Thread_Processing<FileReceiver_Proc>
{
public:
	FileReceiver_Proc(IFileHandler* pFileHandler) 
		: _pFileHandler(pFileHandler) 
		,mh(::ServerMessageHandler){}

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
				pComm->postMessage(mh.GetUserCheckedIn(remoteEp));
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
	MessageHandler& mh;
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
		EndPoint rep("127.0.0.1",2107);

		// MsgReceiver_Proc is your receiver's server message handling
		// FileReceiver_Proc is your receiver's server file handling
		Communicator rcvr(rep);
		MsgHandler<MsgReceiver_Proc> rMsgHandler;
		rMsgHandler.setCommunicator(&rcvr);
		rcvr.attachMsgHandler(&rMsgHandler);
		FileHandler<FileReceiver_Proc> rFileHandler;
		rFileHandler.setFileDestination(".\\Repository\\Temp\\");
		rFileHandler.setCommunicator(&rcvr);
		rcvr.attachFileHandler(&rFileHandler);
		rcvr.setFileSource(".\\Repository\\Package\\");
		rcvr.listen();

		_getche();

	}
	catch(std::exception& ex)
	{
		sout << locker << "\n  " << ex.what() << "\n\n" << unlocker;
	}
}


