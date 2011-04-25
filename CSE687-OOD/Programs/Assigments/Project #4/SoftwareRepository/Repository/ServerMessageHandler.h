#ifndef SERVER_MESSAGE_HANDLER_H
#define SERVER_MESSAGE_HANDLER_H

#include <map>
#include "..\Infrastructure\IMessageHandler.h"
#include "..\Foundation\MsgHandler.h"


class MessageHandler:IMessageHandler
{
public:
	MessageHandler():_metaFolder("MetaXML\\")
		,_pacakgeFolder("Package\\"),_checkinFoler("Temp\\"){}

	virtual Message RespondToMessage(conStrRef message, EndPoint curConnected);
	virtual void ReceiveMessage(conStrRef message );
	virtual Message MessageForSending(MsgType::Value type);


	////
	//virtual void FileProcess(Message msg)
	//{
	//	if(msg.Type()!=Message::MsgType.File)return;
	//}

	//virtual void LoginProcess(Message msg)
	//{
	//	if(msg.Type()!=Message::MsgType.Login)return;

	//}

	//virtual void CheckinProcess(Message msg)
	//{
	//	if(msg.Type()!=Message::MsgType.Checkin)return;

	//}

	//virtual void DependencyProcess(Message msg)
	//{
	//	if(msg.Type()!=Message::MsgType.Dependency)return;

	//}
	strVal MessageHandler::GetKeyName(strVal filePath);
	//void LoadMetaContent(strRef container, conStrRef name);
	virtual Message WarningMessage(strVal warning);

protected:
	//Generate message for sending
	virtual Message FileMessage();
	virtual Message CheckinMessage();
	virtual Message LoginMessage();
	virtual Message DependencyMessage();
	virtual Message AllPackageMesage();

	strVal GetName();
	strVal GetDirectory();

private:
	Message _msg;
	strVal _metaFolder;
	strVal _pacakgeFolder;
	strVal _checkinFoler;
	std::map<EndPoint, strVal> _loginUsers;
	std::string _curUser;
	EndPoint _curIP;

};


#endif