

#include "Message.h"


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

	if(tagName == "Login")type = Login;
	else if(tagName == "Checkin")type = Checkin;
	else if(tagName == "Dependency")type = Dependency;
	else if(tagName == "File")type = File;
	else if(tagName == "Warning")type = Warning;

	else type = Unknown;
}

