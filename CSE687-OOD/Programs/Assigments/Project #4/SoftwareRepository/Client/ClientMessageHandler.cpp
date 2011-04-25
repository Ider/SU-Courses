
#include <iostream>
using namespace std;

#include "ClientMessageHandler.h"
using namespace Ider;

 void MessageHandler::ReceiveMessage(conStrRef message )
 {

 }


 Message MessageHandler::MessageForSending(MsgType::Value type)
 {
	 switch (type)
	 {
	 case MsgType::Login: 
		 return LoginMessage();
	 case MsgType::Dependency: 
		 return DependencyMessage();
	 case MsgType::File: 
		 return FileMessage();
	 case MsgType::Checkin: 
		 return CheckinMessage();
	 default:
		 break;
	 }

	 return Message();
 }


void MessageHandler::FileProcess(Message msg)
{
	if(msg.Type()!=MsgType::File)return;
}

void MessageHandler::LoginProcess(Message msg)
{
	if(msg.Type()!=MsgType::Login)return;

}

void MessageHandler::CheckinProcess(Message msg)
{
	if(msg.Type()!=MsgType::Checkin)return;

}

void MessageHandler::DependencyProcess(Message msg)
{
	if(msg.Type()!=MsgType::Dependency)return;
}

void MessageHandler::WarningProcess(Message msg)
{
	if(msg.Type()!=MsgType::Warning)return;

	cout<<msg.Doc().InnerText()<<endl;
}

Message MessageHandler::FileMessage()
{
	string typeTag = MsgType::EnumToString(MsgType::File);
	string nameTag = "Name";
	//indicate whether extract only this file
	//or full dependencies
	string flagTag = "Full";

	string fileName = "Project #4 Analysis.docx";
	bool flag = false;

	xmlElem elem(nameTag,fileName);
	xmlRep rep(elem.elemStr());

	if (flag) elem = xmlElem(flagTag,"true");
	else elem = xmlElem(flagTag,"false");

	rep.addSibling(elem);
	rep.makeParent(typeTag);

	elem.elemStr() = rep.xmlStr();

	return Message(elem);
}

Message MessageHandler::CheckinMessage()
{
	string typeTag = MsgType::EnumToString(MsgType::Checkin);
	string nameTag = "Action";

	string userName = "Ider";

	xmlElem elem(nameTag,userName);
	xmlRep rep(elem.elemStr());

	rep.makeParent(typeTag);

	elem.elemStr() = rep.xmlStr();

	throw string("To be completed");
	return Message(elem);
}

Message MessageHandler::LoginMessage()
{
	string typeTag = MsgType::EnumToString(MsgType::Login);
	string nameTag = "Name";

	string userName = "Ider";

	xmlElem elem(nameTag,userName);
	xmlRep rep(elem.elemStr());

	rep.makeParent(typeTag);

	elem.elemStr() = rep.xmlStr();

	return Message(elem);
}

Message MessageHandler::DependencyMessage()
{
	string typeTag = MsgType::EnumToString(MsgType::Dependency);
	string nameTag = "Name";

	string depName = "Display";// "*.*";

	xmlElem elem(nameTag,depName);
	xmlRep rep(elem.elemStr());

	rep.makeParent(typeTag);

	elem.elemStr() = rep.xmlStr();

	return Message(elem);
}


#ifdef CLIENT_MESSAGE_HANDLER_TEST

void main()
{
	Message msg;
	MessageHandler mh;


	msg = mh.MessageForSending(MsgType::Login);
	cout<<msg.ToString()<<endl;
	cout<<"Message type: "<<msg.Type()<<endl<<endl;

	msg = mh.MessageForSending(MsgType::Dependency);
	cout<<msg.ToString()<<endl;
	cout<<"Message type: "<<msg.Type()<<endl<<endl;

	msg = mh.MessageForSending(MsgType::File);
	cout<<msg.ToString()<<endl;
	cout<<"Message type: "<<msg.Type()<<endl<<endl;

	//cout<<msg.ToString()<<endl<<endl;
}

#endif

