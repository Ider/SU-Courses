

#include "Message.h"

using namespace std;

MsgType::Value MsgType::StringToEnum(conStrRef type)
{
	if(type == "Login")return Login;
	if(type == "Checkin")return Checkin;
	if(type == "Dependency")return Dependency;
	if(type == "File")return File;
	if(type == "Warning")return Warning;

	return Unknown;
}

strVal MsgType::EnumToString(Value type)
{
	switch(type)
	{
	case Login: 
		return "Login";
	case Dependency: 
		return "Dependency";
	case File: 
		return "File";
	case Checkin: 
		return "Checkin";
	case Warning: 
		return "Warning";
	default:
		break;
	}

	return "Unknown";
}

Message::Message(conStrRef xml)
	:doc(xml)
{
	SetType(doc.Name());
}

void Message::SetMessage(conStrRef xml)
{
	doc.LoadXml(xml);
	SetType(doc.Name());
}


void Message::SetType(strVal tagName)
{
	type = MsgType::StringToEnum(tagName);
}

