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
		Warning,

		Unknown
	};

	Message(){ type = Unknown;}
	Message(conStrRef xml);

	MsgType Type()const{return type;}
	strVal Conntent(){return doc.InnerText();}
	XmlDoc Doc()const{return doc;}
	virtual void SetMessage(conStrRef xml);
	strVal ToString()const{return doc.ToString();}
protected:
	virtual	void  SetType(strVal tagName);

private:
	XmlDoc doc;
	MsgType type;

};


#endif