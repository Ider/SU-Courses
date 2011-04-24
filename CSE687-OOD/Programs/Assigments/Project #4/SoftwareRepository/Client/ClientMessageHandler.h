#ifndef CLIENT_MESSAGE_HANDLER_C_H
#define CLIENT_MESSAGE_HANDLER_C_H

#include "..\Infrastructure\IMessageHandler.h"

class MessageHandler:IMessageHandler
{
public:
	virtual void ReceiveMessage(conStrRef message );
	virtual Message MessageForSending(MsgType::Value type);

	//
	virtual void FileProcess(Message msg);
	virtual void LoginProcess(Message msg);
	virtual void CheckinProcess(Message msg);
	virtual void DependencyProcess(Message msg);
	virtual void WarningProcess(Message msg);


protected:
	virtual Message FileMessage();
	virtual Message CheckinMessage();
	virtual Message LoginMessage();
	virtual Message DependencyMessage();
	//virtual Message WarningMessage(std::string warning);


private:
	Message _msg;
};


#endif