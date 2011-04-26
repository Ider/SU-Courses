
#include <iostream>
#include <stack>
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

	ShowWarning(msg.Doc().InnerText());
}

strVal MessageHandler::Convert(System::String^ s)
{
	strVal temp;
	for(int i=0; i<s->Length; ++i)
		temp += (char)s[i];
	return temp;
}

System::String^ MessageHandler::Convert(conStrRef s)
{
	System::Text::StringBuilder^ temp = gcnew System::Text::StringBuilder();
	for(size_t i=0; i<s.size(); ++i)
		temp->Append((wchar_t)s[i]);
	return temp->ToString();
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
	const MsgType::Value type = MsgType::Login;
	strVal typeTag = MsgType::EnumToString(type);
	strVal nameTag = "Name";

	strVal userName = GetName(type);
	if (userName.size()<=0)return Message();

	xmlElem elem(nameTag,userName);
	xmlRep rep(elem.elemStr());
	rep.makeParent(typeTag);

	elem.elemStr() = rep.xmlStr();

	return Message(elem);
}

Message MessageHandler::DependencyMessage()
{
	const MsgType::Value type = MsgType::Dependency;
	strVal typeTag = MsgType::EnumToString(type);
	strVal nameTag = "Name";

	strVal depName = GetName(type);// "*.*";

	if (depName.size()<=0)return Message();

	xmlElem elem(nameTag,depName);
	xmlRep rep(elem.elemStr());
	rep.makeParent(typeTag);

	elem.elemStr() = rep.xmlStr();

	return Message(elem);
}

strVal MessageHandler::GetName(MsgType::Value type)
{
	System::String^ name;
	switch (type)
	{
	case MsgType::Login: 
		name = _form->UserName();
		break;
	case MsgType::Dependency: 
	case MsgType::File:
		name = _form->SelectedPackageName();
		break;
	case MsgType::Checkin: 
	case MsgType::Warning: 
	default:
		name = System::String::Empty;
		break;
	}
	return Convert(name);
}

void MessageHandler::ShowWarning(strVal warning)
{
	_form->ShowMessageBox(Convert(warning));
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

