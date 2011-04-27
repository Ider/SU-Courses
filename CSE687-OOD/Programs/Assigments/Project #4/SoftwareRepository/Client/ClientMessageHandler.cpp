
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
	strVal tagName ="Name";

	vector<XmlDoc> names = _msg.Doc().Children(tagName);
	size_t count = names.size();
	if (cout<=0)return;

	vector<strVal> files;
	files.reserve(count);
	for (size_t i=0; i<count; ++i)
		files.push_back(names[i].InnerText());

	_form->UploadFiles(files);
}

void MessageHandler::LoginProcess()
{
	if(_msg.Type()!=MsgType::Login)return;

	//request unclosed packages that checked in by this user
	_form->SendMessage(MsgType::Checkin);
	//request all packages in repository
	_form->SendMessage(MsgType::Dependency);
}

void MessageHandler::CheckinProcess()
{
	if(_msg.Type()!=MsgType::Checkin)return;
	
  	System::Collections::Generic::List<System::String^>^ packages
  		=gcnew System::Collections::Generic::List<System::String^>();
   	
	vector<XmlDoc> deps = _msg.Doc().Children("Name");
	strVal name;
	for (size_t i = 0; i<deps.size(); ++i)
	{
		name = deps[i].InnerText();
		packages->Add(Convert(name));
	}

 	_form->Invoke(_form->ShowCheckinListBox,packages);
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

//convert cli String to std::string
strVal MessageHandler::Convert(System::String^ s)
{
	strVal temp;
	for(int i=0; i<s->Length; ++i)
		temp += (char)s[i];
	return temp;
}

//convert std::string to cli String
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
	strVal typeTag = MsgType::EnumToString(type);
	strVal fileName ="*.*";
	strVal tagName = "Name";
	xmlRep  rep;
	
	if (_form->pnlLogin->Visible == true)
	{
		//request all unclosed packages that checked in by this user
		rep.addSibling(xmlElem(tagName,fileName));
		rep.makeParent(typeTag);
		return Message(rep.xmlStr());
	}

	array<System::String^>^ fileNames = _form->fileDialog->FileNames;
	int count = fileNames->Length;
	if (count<=0)return Message(xmlElem::makeTag(typeTag));

	for (int i=0; i<fileNames->Length; ++i)
	{
		fileName = Convert(fileNames[i]);
		rep.addSibling(xmlElem(tagName,fileName));
	}

	rep.makeParent(typeTag);

	return Message(rep.xmlStr());
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
		name = _form->SelectedPackageName();
		break;
	case MsgType::File:
		name = _form->listDep->SelectedItem->ToString();
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

