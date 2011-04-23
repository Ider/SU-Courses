#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

#include "XmlDoc.h"

class Message
{

public:
	enum MsgType
	{
		Login,
		Checkin,
		Dependency,
		File,

		Unknown
	};

	Message(){ type = Unknown;}
	Message();

	MsgType Type(){return type;}
	
	void SetMessage(conStrRef xml);

private:
	void SetType(strVal tagName);
	XmlDoc doc;
	MsgType type;

};


#endif