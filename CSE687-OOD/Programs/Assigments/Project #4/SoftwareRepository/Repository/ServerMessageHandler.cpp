
#include <fstream>

#include "ServerMessageHandler.h"

using namespace std;

void MessageHandler::ReceiveMessage(conStrRef message )
{
	_msg.SetMessage(message);
}

Message MessageHandler::MessageForSending(MsgType::Value type)
{
	switch (_msg.Type())
	{
	case MsgType::Login: 
		return LoginForSending();
	case MsgType::Dependency: 
		return DependencyForSending();
	case MsgType::File: 
		return FileForSending();
	case MsgType::Checkin: 
		return CheckinForSending();
	default:
		break;
	}

	return Message();
}

Message MessageHandler::FileForSending()
{
	string name = GetName();
	string tag = "references";
	XmlDoc doc;
	string xml;
	xmlRep rep;
	
	LoadMetaContent(xml,name);
	doc.LoadXml(xml);
	
	vector<XmlDoc> refs = doc.Children(tag);
	if (refs.size()>0)
	{
		rep.xmlStr() = refs[0].InnerText();
		rep.makeParent("File");
	}
	
	return Message(rep.xmlStr());
}

Message MessageHandler::CheckinForSending()
{
	return Message();
}

Message MessageHandler::LoginForSending()
{
	return Message();
}

Message MessageHandler::DependencyForSending()
{
	return Message();
}

Message MessageHandler::WarningForSending(std::string warning)
{
	string tag = "Warning";
	xmlElem elem(tag,warning);
	return Message(elem);
}

string MessageHandler::GetDirectory()
{
	string path = "Repository\\Ider\\";
	return path;
}

string MessageHandler::GetName()
{
	string tag = "Name";
	XmlDoc doc = _msg.Doc();
	vector<XmlDoc> names = doc.Children(tag);
	if (names.size() <=0)return "";

	return names[0].InnerText();
}

void MessageHandler::LoadMetaContent
	(std::string& container, const std::string& name)
{
	ifstream inf;
	container.clear();

	inf.open(GetDirectory()+name+".xml");
	if (!inf.good())
	{
		std::cout<<"Can't open File "<<name<<".xml"<<std::endl;
		inf.close();
		return;
	}

	char buffer[255];
	while(inf.good())
	{
		inf.getline(buffer,255);
		container += std::string(buffer);
	}

	inf.close();
}
