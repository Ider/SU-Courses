#ifndef SERVER_MESSAGE_HANDLER_H
#define SERVER_MESSAGE_HANDLER_H

#include "..\Infrastructure\IMessageHandler.h"



class MessageHandler:IMessageHandler
{
public:
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
	std::string GetName();
	void LoadMetaContent(std::string& container, const std::string& name);

protected:
	//Generate message for sending
	virtual Message FileForSending();
	virtual Message CheckinForSending();
	virtual Message LoginForSending();
	virtual Message DependencyForSending();
	virtual Message WarningForSending(std::string warning);

	std::string GetDirectory();



private:
	Message _msg;

};


#endif