
#include <iostream>
#include <stack>
using namespace std;

#include "ClientMessageHandler.h"

using namespace Ider;

void MessageHandler::ReceiveMessage(conStrRef message)
{
	_msg.SetMessage(message);
	switch (_msg.Type())
	{
	case MsgType::Login: 
		LoginProcess();
		break;
	case MsgType::Dependency: 
		DependencyProcess();
		break;
	case MsgType::File: 
		FileProcess();
		break;
	case MsgType::Checkin: 
		CheckinProcess();
		break;
	case MsgType::Warning: 
		WarningProcess();
		break;
	default:
		break;
	}

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


void MessageHandler::FileProcess()
{
	if(_msg.Type()!=MsgType::File)return;
}

void MessageHandler::LoginProcess()
{
	if(_msg.Type()!=MsgType::Login)return;

	_form->SendMessage(MsgType::Dependency);
}

void MessageHandler::CheckinProcess()
{
	if(_msg.Type()!=MsgType::Checkin)return;

}

void MessageHandler::DependencyProcess()
{
	if(_msg.Type()!=MsgType::Dependency)return;

  	System::Collections::Generic::List<System::String^>^ packages
  		=gcnew System::Collections::Generic::List<System::String^>();
   	
	vector<XmlDoc> deps = _msg.Doc().Children("Name");
	strVal name;
	for (size_t i = 0; i<deps.size(); ++i)
	{
		name = deps[i].InnerText();
		packages->Add(Convert(name));
	}

 	_form->Invoke(_form->ShowPackageListBox,packages);
}

void MessageHandler::WarningProcess()
{
	if(_msg.Type()!=MsgType::Warning)return;

	ShowWarning(_msg.Doc().InnerText());
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
	const MsgType::Value type = MsgType::File;
	string typeTag = MsgType::EnumToString(type);
	string nameTag = "Name";
	//indicate whether extract only this file
	//or full dependencies
	string flagTag = "Full";

	string fileName = "xmlTran";
	bool flag = false;

	strVal depName = GetName(type);// "*.*";

	if (depName.size()<=0)return Message();

	xmlElem elem(nameTag,depName);
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
	const MsgType::Value type = MsgType::Checkin;
	string typeTag = MsgType::EnumToString(type);
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

