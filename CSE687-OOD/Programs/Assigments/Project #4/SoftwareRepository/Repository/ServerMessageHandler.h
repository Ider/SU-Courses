#ifndef SERVER_MESSAGE_HANDLER_H
#define SERVER_MESSAGE_HANDLER_H

#include <map>
#include "..\Infrastructure\IMessageHandler.h"
#include "..\Foundation\MsgHandler.h"



class MessageHandler:public Ider::IMessageHandler
{
public:
	MessageHandler():_metaFolder("MetaXML\\")
		,_pacakgeFolder("Package\\"),_checkinFoler("Temp\\"){}

	virtual Ider::Message RespondToMessage(conStrRef message, EndPoint curConnected);
	virtual void ReceiveMessage(conStrRef message );
	virtual Ider::Message MessageForSending(Ider::MsgType::Value type);


	////
	//virtual void FileProcess(Ider::Message msg)
	//{
	//	if(msg.Type()!=Ider::Message::Ider::MsgType.File)return;
	//}

	//virtual void LoginProcess(Ider::Message msg)
	//{
	//	if(msg.Type()!=Ider::Message::Ider::MsgType.Login)return;

	//}

	//virtual void CheckinProcess(Ider::Message msg)
	//{
	//	if(msg.Type()!=Ider::Message::Ider::MsgType.Checkin)return;

	//}

	//virtual void DependencyProcess(Ider::Message msg)
	//{
	//	if(msg.Type()!=Ider::Message::Ider::MsgType.Dependency)return;

	//}
	strVal MessageHandler::GetKeyName(strVal filePath);
	//void LoadMetaContent(strRef container, conStrRef name);
	virtual Ider::Message WarningMessage(strVal warning);

protected:
	//Generate message for sending
	virtual Ider::Message FileMessage();
	virtual Ider::Message CheckinMessage();
	virtual Ider::Message LoginMessage();
	virtual Ider::Message DependencyMessage();
	virtual Ider::Message AllPackageMessage();

	strVal GetMessageName();
	strVal GetDirectory();
	bool OKtoCheckin(strVal fileName);

private:
	Ider::Message _msg;
	strVal _metaFolder;
	strVal _pacakgeFolder;
	strVal _checkinFoler;
	std::map<EndPoint, strVal> _loginUsers;
	std::string _curUser;
	EndPoint _curIP;

};


#endif