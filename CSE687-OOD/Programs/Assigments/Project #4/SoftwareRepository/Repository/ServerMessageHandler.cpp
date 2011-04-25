
#include <fstream>
using namespace std;

#include "FileSystem.h"
#include "ServerMessageHandler.h"

Message MessageHandler::RespondToMessage(conStrRef message, EndPoint curConnected)
{
	ReceiveMessage(message);

	_curIP = curConnected;
	map<EndPoint,strVal>::iterator it = _loginUsers.find(_curIP);
	if (it != _loginUsers.end())
		_curUser = it->second;
	
	Message msg = MessageForSending(MsgType::Unknown);

	_curUser.clear();
	return msg;
}

void MessageHandler::ReceiveMessage(conStrRef message)
{
	_msg.SetMessage(message);
}

Message MessageHandler::MessageForSending(MsgType::Value type)
{
	if (_msg.Type()!= MsgType::Login && _curUser.size()<=0)
		return WarningMessage("No user connected");

	switch (_msg.Type())
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
		return WarningMessage("Unknown message type.");
		break;
	}

	return Message();
}

Message MessageHandler::FileMessage()
{
	//recursion not implemented

	strVal name = GetName();
	strVal path = GetDirectory()+_metaFolder+name+".xml";
	strVal tag = "references";
	strVal content;
	XmlDoc doc;
	xmlRep rep;
	
	if (!doc.LoadXmlFile(path))
		return WarningMessage(name+": the package is not in the repository.");

	vector<XmlDoc> refs = doc.Children(tag);

	if (refs.size()<=0)
		return WarningMessage(name+": the package does not depend on other package.");

	doc.elemStr() = refs[0].elemStr();
	refs = doc.Children();

	if (refs.size()<=0)
		return WarningMessage(name+": the package does not depend on other package.");

	tag = "Name";
	for (size_t i=0; i<refs.size(); ++i)
	{
		content = refs[i].InnerText();
		content = GetKeyName(content);
		xmlElem elem(tag,content);
		rep.addSibling(elem);
	}

	tag = MsgType::EnumToString(MsgType::Dependency);
	rep.makeParent(tag);

	return Message(rep.xmlStr());
}

Message MessageHandler::CheckinMessage()
{
	const strVal name = GetName();
	strVal tag = "User";
	strVal content;
	XmlDoc doc;
	xmlRep rep;
	return Message();
}

Message MessageHandler::LoginMessage()
{
	strVal path = GetDirectory()+"Users.xml";
	XmlDoc doc;
	
	if (!doc.LoadXmlFile(path))
		return WarningMessage("Users file broken, please contact administrator.");
	
	strVal name = GetName();
	strVal tag = "User";
	strVal content;
	xmlRep rep;

	vector<XmlDoc> users = doc.Children(tag);

	for (size_t i=0; i<users.size();++i)
	{
		strVal userName = users[i].Children("Name")[0].InnerText();
		if (userName == name)
		{
			_loginUsers[_curUser] = name;
			return _msg;
		}
	}

	return WarningMessage("User is not in the repository.");
}

Message MessageHandler::DependencyMessage()
{
	const strVal name = GetName();
	
	if (name == "*.*")return AllPackageMesage();
	
	strVal path = GetDirectory()+_metaFolder+name+".xml";
	strVal tag = "references";
	strVal content;
	XmlDoc doc;
	xmlRep rep;

	if (!doc.LoadXmlFile(path))
		return WarningMessage(name+": the package is not in the repository.");
	
	vector<XmlDoc> refs = doc.Children(tag);
	if (refs.size()<=0)
		return WarningMessage(name+": the package does not depend on other package.");

	//find all dependency children under dependency tag
	refs = refs[0].Children();
	if (refs.size()<=0)
		return WarningMessage(name+": the package does not depend on other package.");
	
	tag = "Name";
	for (size_t i=0; i<refs.size(); ++i)
	{
		content = refs[i].InnerText();
		content = GetKeyName(content);
		xmlElem elem(tag,content);
		rep.addSibling(elem);
	}
	
	tag = MsgType::EnumToString(MsgType::Dependency);
	rep.makeParent(tag);

	return Message(rep.xmlStr());
}

Message MessageHandler::WarningMessage(strVal warning)
{
	strVal tag = MsgType::EnumToString(MsgType::Warning);
	xmlElem elem(tag,warning);
	return Message(elem);
}

Message MessageHandler::AllPackageMesage()
{
	strVal path = GetDirectory() + "MetaXML";
	strVal tag = "Name";
	WinTools_Extracts::FileHandler fh;
	xmlRep rep;
	vector<strVal> files = fh.getFileSpecs(path,"*.xml");
	
	for (size_t i=0; i<files.size(); ++i)
	{
		xmlElem elem (tag,GetKeyName(files[i]));
		rep.addSibling(elem);
	}
	
	tag = MsgType::EnumToString(MsgType::Dependency);
	rep.makeParent(tag);

	return Message(rep.xmlStr());
}


strVal MessageHandler::GetDirectory()
{
	strVal path = ".\\Repository\\";
	return path;
}

strVal MessageHandler::GetName()
{
	strVal tag = "Name";
	XmlDoc doc = _msg.Doc();
	vector<XmlDoc> names = doc.Children(tag);
	if (names.size() <=0)return "";
	strVal name = names[0].InnerText();
	return names[0].InnerText();
}
// 
// void MessageHandler::LoadMetaContent(strRef container, conStrRef name)
// {
// 	ifstream inf;
// 	container.clear();
// 	strVal path = GetDirectory()+_metaFolder+name+".xml";
// 
// 	inf.open(path);
// 	if (!inf.good())
// 	{
// 		//std::cout<<"Can't open File "<<name<<".xml"<<std::endl;
// 		inf.close();
// 		return;
// 	}
// 
// 	char buffer[255];
// 	while(inf.good())
// 	{
// 		inf.getline(buffer,255);
// 		container += strVal(buffer);
// 	}
// 
// 	inf.close();
// }
// 


//////////////////////////////////////////////////////////////////////////
//Remove the path and file extension, return the pure file name
strVal MessageHandler::GetKeyName(strVal filePath)
{
	//remove path
	//If filePath.find_last_of('\\') failed, it return std::string::npos
	//npos + 1 equals to 0, so nothing erased
	filePath.erase(0,filePath.find_last_of('\\')+1);
	//remove extension
	size_t pos = filePath.find_last_of('.');
	if (pos < filePath.size())
		filePath.erase(pos,filePath.size());

	return filePath;
}




void main()
{
	string msg ="<Login><Name>Ider</Name></Login>";

	MessageHandler mh;
	Message snd = mh.RespondToMessage(msg,EndPoint());
	cout<<snd.ToString()<<endl;
	cout<<"Message type: "<<snd.Type()<<endl<<endl;

	msg ="<Dependency><Name>*.*</Name></Dependency>";
	snd = mh.RespondToMessage(msg,EndPoint());
	cout<<snd.ToString()<<endl;
	cout<<"Message type: "<<snd.Type()<<endl<<endl;

	msg ="<Dependency><Name>Display</Name></Dependency>";
	snd = mh.RespondToMessage(msg,EndPoint());
	cout<<snd.ToString()<<endl;
	cout<<"Message type: "<<snd.Type()<<endl<<endl;


	msg ="*.*";
	snd = mh.RespondToMessage(msg,EndPoint());
	cout<<snd.ToString()<<endl;
	cout<<"Message type: "<<snd.Type()<<endl<<endl;
}
#ifdef SERVER_MESSAGE_HANDLER_TEST

#endif
