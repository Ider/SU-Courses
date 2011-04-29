
#ifndef SERVER_MESSAGE_HANDLER_H
#define SERVER_MESSAGE_HANDLER_H
/////////////////////////////////////////////////////////////////////////
//  ServerMessageHandler.cpp    -  Server side message handler   	   //
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
   This module provide server side message

   Public Interface:
   =================
   FormMessageHanlder->ReceiveMessage(msg);
   

   Build Process:
   ==============
   Required Files:
     MsgHandler.h, MsgHandler.cpp, IMessageHandler.h
*/


#include <map>
#include "..\Infrastructure\IMessageHandler.h"
#include "..\Foundation\MsgHandler.h"


class MessageHandler:public Ider::IMessageHandler
{
public:
	//constructor
	MessageHandler():_metaFolder("MetaXML\\")
		,_pacakgeFolder("Package\\")
		,_checkinFoler("Temp\\"),
		_repositoryPath("..\\RepositoryLibrary\\")
	{}
	//destructor
	virtual ~MessageHandler(){}

	//Generate a message base on received message
	virtual Ider::Message RespondToMessage(conStrRef message, EndPoint curConnected);
	//Implement IMessageHandler Interface
	virtual void ReceiveMessage(conStrRef message );
	virtual Ider::Message MessageForSending(Ider::MsgType::Value type);
	virtual Ider::Message WarningMessage(strVal warning);


	//Auxiliary function
	strVal MessageHandler::GetKeyName(strVal filePath);

	//Data Accessors
	strRef MetaFolder(){return _metaFolder;}
	strRef PackageFolder(){return _pacakgeFolder;}
	strRef ChickinFolder(){return _checkinFoler;}
	strRef RepositoryPath(){return _repositoryPath;}

	//Build Metadata for just uploaded file
	bool BuildCheckinMetadata(strVal fileName,EndPoint curConnected);


protected:
	//Generate message for sending
	virtual Ider::Message FileMessage();
	virtual Ider::Message CheckinMessage();
	virtual Ider::Message LoginMessage();
	virtual Ider::Message DependencyMessage();
	virtual Ider::Message CommitMessage();
	virtual Ider::Message PackageMessage();

	virtual Ider::Message AllPackageMessage();
	virtual Ider::Message GetUserCheckedIn();

	//Auxiliary function
	strVal GetMessageName();
	bool OKtoCheckin(strVal fileName);
	bool BuildMetadata(strVal fileName);

private:
	//data
	Ider::Message _msg;
	//repository folders path
	strVal _metaFolder;
	strVal _pacakgeFolder;
	strVal _checkinFoler;
	strVal _repositoryPath;
	//user connection info
	std::map<EndPoint, strVal> _loginUsers;
	strVal _curUser;
	EndPoint _curIP;
	
};


#endif