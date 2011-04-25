#ifndef CLIENT_MESSAGE_HANDLER_C_H
#define CLIENT_MESSAGE_HANDLER_C_H

#include "..\Infrastructure\IMessageHandler.h"

class MessageHandler:public Ider::IMessageHandler
{
public:
	virtual void ReceiveMessage(conStrRef message );
	virtual Ider::Message MessageForSending(Ider::MsgType::Value type);

	//
	virtual void FileProcess(Ider::Message msg);
	virtual void LoginProcess(Ider::Message msg);
	virtual void CheckinProcess(Ider::Message msg);
	virtual void DependencyProcess(Ider::Message msg);
	virtual void WarningProcess(Ider::Message msg);


protected:
	virtual Ider::Message FileMessage();
	virtual Ider::Message CheckinMessage();
	virtual Ider::Message LoginMessage();
	virtual Ider::Message DependencyMessage();
	//virtual Ider::Message WarningMessage(std::string warning);


private:
	Ider::Message _msg;
};


#endif