#ifndef CLIENT_MESSAGE_HANDLER_C_H
#define CLIENT_MESSAGE_HANDLER_C_H
/////////////////////////////////////////////////////////////////////////
//  ClientMessageHandler.h    - Client side message handler		       //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 2010                               //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #4	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////
/*
   Module Operations:
   ==================
   This module provides class to handler the message sent from server,
   and send messages to server to request data.

   This 

   The class must inherit from template Thread_Processing<typename T>
   where the typename should be itself.

   Public Interface:
   =================
   ClientMessage_Proc.run()
   ClientFile_Proc.run()

   Build Process:
   ==============
   Required Files:
     ClientMessageHandler.h, ClientMessageHandler.cpp, Communicator.h

*/


#include "..\Infrastructure\IMessageHandler.h"
#include "UserInterface.h"

//#include <conio.h>
#include <vcclr.h>

//Declare UserInterface /*Syntax "ref class Client::UserInter;" is error */
 namespace Client
 {
 	ref class UserInterface;
 }

class MessageHandler:public Ider::IMessageHandler
{
public:
	//constructors
	MessageHandler(){}
	MessageHandler(Client::UserInterface^ form){_form = form;}
	//destructor
	virtual ~MessageHandler(){}

	//Implement IMessageHandler interface
	virtual void ReceiveMessage(conStrRef message );
	virtual Ider::Message MessageForSending(Ider::MsgType::Value type);

	//convert operation between cli String and std string
	strVal Convert(System::String^ s);
	System::String^ Convert(conStrRef s);

	void SetForm(Client::UserInterface^ form){_form = form;}

protected:
	//Process message
	virtual void LoginProcess();
	virtual void DependencyProcess();
	virtual void PackageProcess();
	virtual void FileProcess();
	virtual void CheckinProcess();
	virtual void CommitProcess();
	virtual void WarningProcess();

	//Messages for sending
	virtual Ider::Message LoginMessage();
	virtual Ider::Message DependencyMessage();
	virtual Ider::Message FileMessage();
	virtual Ider::Message PackageMessage();
	virtual Ider::Message CheckinMessage();
	virtual Ider::Message CommitMessage();

	//Auxiliary function
	strVal GetName(Ider::MsgType::Value type);
	void ShowWarning(strVal warning);

private:
	//current received message
	Ider::Message _msg;
	gcroot<Client::UserInterface^> _form;
};


#endif