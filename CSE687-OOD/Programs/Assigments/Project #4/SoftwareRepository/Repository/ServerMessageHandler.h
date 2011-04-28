#ifndef SERVER_MESSAGE_HANDLER_H
#define SERVER_MESSAGE_HANDLER_H

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
		_repositoryPath(".\\Repository\\"){}

	//Generate a message base on received message
	virtual Ider::Message RespondToMessage(conStrRef message, EndPoint curConnected);
	//Implement IMessageHandler Interface
	virtual void ReceiveMessage(conStrRef message );
	virtual Ider::Message MessageForSending(Ider::MsgType::Value type);
	virtual Ider::Message WarningMessage(strVal warning);


	//Auxiliary function
	strVal MessageHandler::GetKeyName(strVal filePath);
	bool BuildCheckinMetadata(strVal fileName,EndPoint curConnected);

	//Data Accessors
	strRef MetaFolder(){return _metaFolder;}
	strRef PackageFolder(){return _pacakgeFolder;}
	strRef ChickinFolder(){return _checkinFoler;}
	strRef RepositoryPath(){return _repositoryPath;}

protected:
	//Generate message for sending
	virtual Ider::Message FileMessage();
	virtual Ider::Message CheckinMessage();
	virtual Ider::Message LoginMessage();
	virtual Ider::Message DependencyMessage();

	virtual Ider::Message AllPackageMessage();
	virtual Ider::Message GetUserCheckedIn();

	//Auxiliary function
	strVal GetMessageName();
	strVal GetDirectory();
	bool OKtoCheckin(strVal fileName);
	bool BuildMetadata(strVal fileName);

private:
	Ider::Message _msg;
	strVal _metaFolder;
	strVal _pacakgeFolder;
	strVal _checkinFoler;
	strVal _repositoryPath;
	std::map<EndPoint, strVal> _loginUsers;
	strVal _curUser;
	EndPoint _curIP;
	
};


#endif