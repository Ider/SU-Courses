/////////////////////////////////////////////////////////////////////////
//  Includes.cpp    -  Program entry point					  		   //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 2010                               //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #4	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////
#include "UserInterface.h"

using namespace Client ;

extern Ider::IMessageHandler* FormMessageHanlder;


[STAThreadAttribute]
int main(array<System::String ^> ^args)
{

	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// compose form and message hanlder
	UserInterface^ ui = gcnew UserInterface();
	MessageHandler* mh = new MessageHandler(ui);
	ui->SetMessageHandler(mh);

	//set globe variable
	FormMessageHanlder = mh;
	//run form
	Application::Run(ui);

	delete mh;
	return 0;
}