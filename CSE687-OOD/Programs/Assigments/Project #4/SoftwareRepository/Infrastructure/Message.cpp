/////////////////////////////////////////////////////////////////////////
//  Message.cpp    -  Message class and message type enum   		   //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 2010                               //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #4	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////


using namespace std;

#include "Message.h"

using namespace Ider;

//////////////////////////////////////////////////////////////////////////
//Convert string to Message enum type
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

//////////////////////////////////////////////////////////////////////////
//Convert message enum type to string
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

//////////////////////////////////////////////////////////////////////////
//constructor
Message::Message(conStrRef xml)
	:doc(xml)
{
	SetType(doc.Name());
}

//////////////////////////////////////////////////////////////////////////
//set xml content to message
void Message::SetMessage(conStrRef xml)
{
	doc.LoadXml(xml);
	SetType(doc.Name());
}


//////////////////////////////////////////////////////////////////////////
//Set the type base on first tag name value
void Message::SetType(strVal tagName)
{
	type = MsgType::StringToEnum(tagName);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////< test stub >///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#ifdef MESSAGE_TEST


void main()
{
	strVal xml ="<Login><Name>Ider</Name></Login>";
	

	Message msg(xml);

	cout<<msg.Type()<<endl;
	cout<<msg.ToString();
}

#endif
