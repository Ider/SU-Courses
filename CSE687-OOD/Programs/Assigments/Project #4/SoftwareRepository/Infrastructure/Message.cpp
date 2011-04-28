using namespace std;

#include "Message.h"

using namespace Ider;

MsgType::Value MsgType::StringToEnum(conStrRef type)
{
	if(type == "Login")return Login;
	if(type == "Package")return Package;
	if(type == "Dependency")return Dependency;
	if(type == "File")return File;
	if(type == "Checkin")return Checkin;
	if(type == "Commit")return Commit;
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
	case Package: 
		return "Package";
	case Commit: 
		return "Commit";
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

