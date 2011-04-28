
#include <fstream>
using namespace std;

#include "FileSystem.h"
#include "ServerMessageHandler.h"
#include "..\XmlMetadataManager\Includes.h"
#include "..\XmlMetadataManager\MetaGenerator.h"
#include "..\XmlMetadataManager\PackageInfo.h"

using namespace Ider;

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

//////////////////////////////////////////////////////////////////////////
//receive a message from client
void MessageHandler::ReceiveMessage(conStrRef message)
{
	_msg.SetMessage(message);
}

//////////////////////////////////////////////////////////////////////////
//generate a message base on type
//the MsgType of return message may not be the same as type
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

//////////////////////////////////////////////////////////////////////////
//generate a File type message
Message MessageHandler::FileMessage()
{
	//recursion not implemented

	strVal name = GetMessageName();
	strVal path = _repositoryPath+_metaFolder+name+".xml";

	ifstream inf;
	inf.open(path);

	if(!inf.good())
	{
		Message message = WarningMessage(name+": the package is not in the repository.");
		inf.close();
		return message;
	}

	inf.close();

	xmlRep rep;

	strVal tag = "Name";
	xmlElem elem(tag,name);
	rep.addSibling(elem);

	tag = MsgType::EnumToString(MsgType::File);
	rep.makeParent(tag);

	return Message(rep.xmlStr());
}

//////////////////////////////////////////////////////////////////////////
//generate a File type message if ok to check in
Message MessageHandler::CheckinMessage()
{
	strVal tag = "Name";
	vector<XmlDoc> files = _msg.Doc().Children(tag);
	if (files.size()<=0)return WarningMessage("Please specify package.");
	

	if (files[0].InnerText()=="*.*")
		return GetUserCheckedIn();
	
	strVal fileName;
	strVal warning;
	strVal prefix = "\n  ";

	//check every file whether it is ok to check in
	for (size_t i=0; i<files.size(); ++i)
	{
		fileName = files[i].InnerText();
		if (!OKtoCheckin(fileName))
			warning+=prefix+fileName;
	}

	//if at least one of the check in file is
	//not ok to check in, check in failed
	if (warning.size()>0)
	{
		warning = "Failed to upload.\n\n"
			+("Follow files are already in the repository:\n"
			+ warning)
			+ "\n\nUnfortunately you are not the owner.";
		return WarningMessage(warning);
	}

	//send file message to request file from client
	xmlRep rep;
	tag = MsgType::EnumToString(MsgType::File);
	rep.xmlStr() = _msg.Doc().InnerText();
	rep.makeParent(tag);

	return Message(rep.xmlStr());
}

//////////////////////////////////////////////////////////////////////////
//check whether user that request to log in from client side is in the repository
//if so return Login type message
//else return warning.
Message MessageHandler::LoginMessage()
{
	strVal path = _repositoryPath+"Users.xml";
	XmlDoc doc;
	
	if (!doc.LoadXmlFile(path))
		return WarningMessage("Users file broken, please contact administrator.");
	
	strVal name = GetMessageName();
	strVal tag = "User";
	strVal content;
	xmlRep rep;

	vector<XmlDoc> users = doc.Children(tag);

	for (size_t i=0; i<users.size();++i)
	{
		strVal userName = users[i].Children("Name")[0].InnerText();
		if (userName == name)
		{
			_loginUsers[_curIP] = name;
			return _msg;
		}
	}

	return WarningMessage("User is not in the repository.");
}

//////////////////////////////////////////////////////////////////////////
//generate a Dependency type message
Message MessageHandler::DependencyMessage()
{
	const strVal name = GetMessageName();
	
	if (name == "*.*")return AllPackageMessage();
	
	strVal path = _repositoryPath+_metaFolder+name+".xml";
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


Message MessageHandler::CommitMessage()
{
	ClosePackage();
	return WarningMessage("OK!!!");
}


Message MessageHandler::PackageMessage()
{
	return Message("Not implemented.");
}

//////////////////////////////////////////////////////////////////////////
//generate a File type message
Message MessageHandler::WarningMessage(strVal warning)
{
	strVal tag = MsgType::EnumToString(MsgType::Warning);
	xmlElem elem(tag,warning);
	return Message(elem);
}

//////////////////////////////////////////////////////////////////////////
//generate a Dependency type message, it contains all packages in repository
Message MessageHandler::AllPackageMessage()
{
	strVal path = _repositoryPath + _metaFolder;
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

//////////////////////////////////////////////////////////////////////////
//generate a Checkin type message
Message MessageHandler::GetUserCheckedIn()
{
	strVal path = _repositoryPath + _checkinFoler;
	strVal tag = "Name";
	strVal fileName;
	WinTools_Extracts::FileHandler fh;
	xmlRep rep;
	vector<strVal> files = fh.getFileSpecs(path,"*.xml");

	for (size_t i=0; i<files.size(); ++i)
	{
		fileName = GetKeyName(files[i]);
		
		//since the package is already in repository
		//OKtoCheckin will return true only when user is owner
		if (OKtoCheckin(fileName))
		{
			xmlElem elem (tag,fileName);
			rep.addSibling(elem);
		}
	}

	tag = MsgType::EnumToString(MsgType::Checkin);
	rep.makeParent(tag);

	return Message(rep.xmlStr());
}

//////////////////////////////////////////////////////////////////////////
//Build meta data file
bool MessageHandler::BuildCheckinMetadata(strVal fileName,EndPoint curConnected)
{
 	map<EndPoint,strVal>::iterator it = _loginUsers.find(curConnected);
 	if (it == _loginUsers.end()) 
 		return false;
 
 	//start save xml file
 
	strVal userName = it->second;
	fileName = GetKeyName(fileName);
	strVal path = _repositoryPath+_checkinFoler;

	PackageInfo pack;
	pack.Name() = fileName;
	pack.AddFileName(path+fileName+".h");
	pack.AddFileName(path+fileName+".cpp");

	ifstream fIn;
	Includes inc(&fIn);
	MetaGenerator gen(&inc);

	gen.OwnerName()=userName;

	XmlDoc doc(gen.GetMetadata(pack));
	
	return doc.SaveToFile(path+fileName+".xml");
}


bool MessageHandler::ClosePackage()
{
	strVal tag ="Name";
	vector<XmlDoc> files = _msg.Doc().Children(tag);
	if (files.size() <=0)return true;

	strVal fileName;
	strVal command;
	strVal sourceFolder = _repositoryPath+_checkinFoler;
	strVal destFolder = _repositoryPath+_pacakgeFolder;;
	vector<strVal> fileNames;

	for (size_t i = 0; i<files.size(); ++i)
	{
		fileName = GetKeyName(files[i]);
		if (!OKtoCheckin(fileName))continue;

		command = "move /y "+ sourceFolder + fileName+".h "+destFolder;
		system(command.c_str());
		command = "move /y "+ sourceFolder + fileName+".h "+destFolder;
		system(command.c_str());
		
		BuildMetadata(fileName);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
//Build meta data file
bool MessageHandler::BuildMetadata(strVal fileName)
{
	fileName = GetKeyName(fileName);
	strVal path = _repositoryPath+_pacakgeFolder;

	strVal command = "del "+ _repositoryPath 
		+ _checkinFoler + fileName+".xml ";
	system(command.c_str());

	PackageInfo pack;
	pack.Name() = fileName;
	pack.AddFileName(path+fileName+".h");
	pack.AddFileName(path+fileName+".cpp");

	ifstream fIn;
	Includes inc(&fIn);
	MetaGenerator gen(&inc);

	gen.OwnerName()=_curUser;

	XmlDoc doc(gen.GetMetadata(pack));

	path = _repositoryPath+_metaFolder;
	return doc.SaveToFile(path+fileName+".xml");
}

//////////////////////////////////////////////////////////////////////////
//Extract InnerText of Name tag in message
strVal MessageHandler::GetMessageName()
{
	strVal tag = "Name";
	XmlDoc doc = _msg.Doc();
	vector<XmlDoc> names = doc.Children(tag);
	if (names.size() <=0)return "";
	strVal name = names[0].InnerText();
	return names[0].InnerText();
}

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

//////////////////////////////////////////////////////////////////////////
//check whether uploaded file is not in repository
//or user own the file
bool MessageHandler::OKtoCheckin(strVal fileName)
{
	fileName = GetKeyName(fileName)+".xml";

	XmlDoc doc;

	//package not in the repository, ok to check in
	if (!doc.LoadXmlFile(_repositoryPath+_metaFolder+fileName))
		if (!doc.LoadXmlFile(_repositoryPath+_checkinFoler+fileName))
			return true;

	vector<XmlDoc> elems = doc.Children("owner");
	if (elems.size()<=0)return false;

	//check in depend on whether user is package owner
	strVal owner = elems[0].InnerText();
	return owner == _curUser;
}


#ifdef SERVER_MESSAGE_HANDLER_TEST


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

#endif
