#ifndef IMESSAGE_HANDLER_H
#define IMESSAGE_HANDLER_H

#include "Message.h"

namespace Ider
{
	class IMessageHandler
	{
	public:
		virtual void ReceiveMessage(conStrRef message )=0;
		virtual Message MessageForSending(MsgType::Value type)=0;
	};

}


#endif