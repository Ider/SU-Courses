
#include <fstream>
using namespace std;

#include "FileSystem.h"
#include "ServerMessageHandler.h"
using namespace WinTools_Extracts;

void MessageHandler::ReceiveMessage(conStrRef message )
{
	_msg.SetMessage(message);
}

Message MessageHandler::MessageForSending(MsgType::Value type)
{
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
	strVal name = GetName();
	strVal tag = "references";
	XmlDoc doc;
	xmlRep rep;
	
	LoadMetaContent(doc.elemStr(),name);
	
	vector<XmlDoc> refs = doc.Children(tag);
	if (refs.size()>0)
	{
		rep.xmlStr() = refs[0].InnerText();
		tag = MsgType::EnumToString(MsgType::File);
		rep.makeParent(tag);
	}
	
	return Message(rep.xmlStr());
}

Message MessageHandler::CheckinMessage()
{
	return Message();
}

Message MessageHandler::LoginMessage()
{
	return Message();
}

Message MessageHandler::DependencyMessage()
{
	const strVal name = GetName();
	strVal tag = "references";
	strVal content;
	XmlDoc doc;
	xmlRep rep;

	if (name == "*.*")return AllPackageMesage();

	LoadMetaContent(doc.elemStr(),name);
	if (doc.elemStr().size()<=0)
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
		content = refs[i].body();
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
	FileHandler fh;
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
	strVal path = ".\\Repository\\Ider\\";
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

void MessageHandler::LoadMetaContent
	(strRef container, conStrRef name)
{
	ifstream inf;
	container.clear();
	strVal path = GetDirectory()+_metaFolder+name+".xml";

	inf.open(path);
	if (!inf.good())
	{
		//std::cout<<"Can't open File "<<name<<".xml"<<std::endl;
		inf.close();
		return;
	}

	char buffer[255];
	while(inf.good())
	{
		inf.getline(buffer,255);
		container += strVal(buffer);
	}

	inf.close();
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

	Trim(filePath);
	return filePath;
}

//////////////////////////////////////////////////////////////////////////
//Removes all occurrences of white space characters from the beginning and 
//end of string. 
void MessageHandler::Trim(strRef value)
{
	const char * ch = value.c_str();
	size_t top = 0;
	size_t end = value.size() - 1;
	while(top <= end && 
		(ch[top] ==' ' || ch [top] == '\t'))
		++top;
	while(end >=0 && (ch[end] ==' ' || ch [end] == '\t'))
		--end;

	top = (top >= value.size())?top = 0 : top;
	end  =  end<0? end = value.size() : end+1;

	value.erase(end,value.size());
	value.erase(0,top);

}


#ifdef SERVER_MESSAGE_HANDLER_TEST

void main()
{
	string msg ="<Dependency><Name>Display</Name></Dependency>";

	MessageHandler mh;
	mh.ReceiveMessage(msg);
	Message snd = mh.MessageForSending(MsgType::Unknown);

	cout<<snd.ToString()<<endl;
	cout<<"Message type: "<<snd.Type()<<endl<<endl;

	//msg ="<Dependency><Name>Hello</Name></Dependency>";

	msg ="*.*";
	mh.ReceiveMessage(msg);
	snd = mh.MessageForSending(MsgType::Unknown);

	cout<<snd.ToString()<<endl;
	cout<<"Message type: "<<snd.Type()<<endl<<endl;
}

#endif
