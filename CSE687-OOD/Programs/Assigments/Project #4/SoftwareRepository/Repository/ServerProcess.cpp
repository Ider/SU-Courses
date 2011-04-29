/////////////////////////////////////////////////////////////////////////
//  ServerProcess.cpp    -  Server side thread process	     		   //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 2010                               //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #4	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////


#include "ServerProcess.h"
#include <vector>
#include <conio.h>
using namespace std;
using namespace Ider;

//definition of static data
MessageHandler ServerMessageHandlerInstant::instant;

void ServerMessage_Proc::run()
{
	GLock<1> lock;
	std::string msg;
	lock.lock();
	BQueue<std::string>* pBQ = _pMsgHandler->getQueue();
	ICommunicator* pComm = _pMsgHandler->getCommunicator();
	lock.unlock();

	while(true)
	{
		sout << locker << "\n\n  Server processing message: \n" 
			<< (msg = pBQ->deQ()).c_str() << unlocker;
		lock.lock();
		EndPoint remoteEp = _pMsgHandler->getEndPoint();
		if(pComm->connect(remoteEp.getIP(), remoteEp.getPort()))
		{
			Message receivedMsg(msg);//received me

			Message msgToSend = mh.RespondToMessage(receivedMsg,remoteEp);

			//request for file, response file, then post files
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
	}
}

void ServerMessage_Proc::PostFile(Message msg)
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

void ServerFile_Proc::run()
{

	GLock<1> lock;
	std::string msg;
	lock.lock();
	BQueue<std::string>* pBQ = _pFileHandler->getQueue();
	ICommunicator* pComm = _pFileHandler->getCommunicator();
	lock.unlock();

	while(true)
	{
		sout << locker << "\n\n  Server processing file: \n" 
			<< (msg = pBQ->deQ()).c_str() << unlocker;
		lock.lock();
		EndPoint remoteEp = _pFileHandler->getEndPoint();
		if(pComm->connect(remoteEp.getIP(), remoteEp.getPort()))
		{
			mh.BuildCheckinMetadata(msg,remoteEp);
			pComm->postMessage(std::string(" File received: ")+msg);
			pComm->disconnect();
		}
		else
			sout << "\n  failed to connect";
		lock.unlock();
	}
}


void main()
{
	sout << locker << "\n  Running Socket Communicator Server"
		<< "\n =============================\n" << unlocker;

 	try
 	{
 		EndPoint rep("127.0.0.1",2107);
		MessageHandler& mh = ServerMessageHandlerInstant::Value();
 
 		// MsgReceiver_Proc is your receiver's server message handling
 		// FileReceiver_Proc is your receiver's server file handling
 		Communicator rcvr(rep);
 		MsgHandler<ServerMessage_Proc> rMsgHandler;
 		rMsgHandler.setCommunicator(&rcvr);
 		rcvr.attachMsgHandler(&rMsgHandler);
 		FileHandler<ServerFile_Proc> rFileHandler;
 		rFileHandler.setFileDestination(mh.RepositoryPath()+mh.ChickinFolder());
 		rFileHandler.setCommunicator(&rcvr);
 		rcvr.attachFileHandler(&rFileHandler);
 		rcvr.setFileSource(mh.RepositoryPath()+mh.PackageFolder());
 		rcvr.listen();
 
 		_getche();
 
 	}
 	catch(std::exception& ex)
 	{
 		sout << locker << "\n  " << ex.what() << "\n\n" << unlocker;
 	}
}

#ifdef SERVER_PROCESS_TEST
#endif

