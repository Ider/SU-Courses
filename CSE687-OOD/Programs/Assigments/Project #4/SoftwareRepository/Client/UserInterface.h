#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H


#include "ClientMessageHandler.h"
#include "ClientProcess.h"

class MessageHandler;

#pragma once

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for UserInterface
	/// </summary>
	public ref class UserInterface : public System::Windows::Forms::Form
	{
	public:
		UserInterface(void)
		{
			InitializeComponent();
		}

		UserInterface(ICommunicator* sender)
		{
			this->sender = sender;
			this->selectionTrack = gcnew System::Collections::Generic::List<String^>();
			//SendMessage(Ider::MsgType::Login);
			InitializeComponent();
		}

		void SetMessageHandler(Ider::IMessageHandler* mh)
		{
			this->mh=mh;
		}

		void ShowMessageBox(String^ msg)
		{
			System::Windows::Forms::MessageBox::Show(msg, "Warning", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		bool SendMessage(Ider::MsgType::Value type)
		{
			Ider::Message msg = this->mh->MessageForSending(type);

			if (msg.Type()==Ider::MsgType::Unknown)return false;

			this->sender->postMessage(msg);
			return true;
		}

		String^ SelectedPackageName(void)
		{
			if (this->selectionTrack->Count<=0)
			{
				this->selectionTrack->Add(L"*.*");
				return L"*.*";
			}

			int index = this->listDep->SelectedIndex;
			if(index<0)
			{
				ShowMessageBox(L"Please select a package name.");
				return "";
			}

			if(index==0)
			{
				if (this->selectionTrack->Count<=1)
				{
					//"*.*" will not be pop up, to indicate the highest top
					ShowMessageBox(L"Could not go back any more.");
					return "";
				}
				else
				{
					//get last requested name
					int last = this->selectionTrack->Count-1;
					String^ name = this->selectionTrack[last];
					this->selectionTrack->RemoveAt(last);
					return name;
				}
			}

			return this->listDep->SelectedItem->ToString();
		}

		void ShowPackageListBox(System::Collections::Generic::List<String^>^ packages)
		{
			//this->selectionTrack->Add(this->listDep->SelectedItem->ToString());
			this->listDep->Items->Clear();
			this->listDep->Items->Add("..");

			for (System::Int32 i=0; i<packages->Count; ++i)
			{
				this->listDep->Items->Add(packages[i]);
			}
		}

	public: System::Windows::Forms::TabControl^  tabClient;
	public: System::Windows::Forms::TabPage^  tabPackage;
	public: System::Windows::Forms::TabPage^  tabCheckin;
	public: System::Windows::Forms::ListBox^  listDep;

	public: System::Windows::Forms::Button^  btnDep;
	public: System::Windows::Forms::Button^  btnExt;
	private: System::Windows::Forms::Button^  button1;
	public: 
	public: System::Windows::Forms::Panel^  pnlLogin;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UserInterface()
		{
			if (components)
			{
				delete components;
				delete mh;
			}
		}


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>

		void InitializeComponent(void)
		{
			this->tabClient = (gcnew System::Windows::Forms::TabControl());
			this->tabPackage = (gcnew System::Windows::Forms::TabPage());
			this->btnDep = (gcnew System::Windows::Forms::Button());
			this->btnExt = (gcnew System::Windows::Forms::Button());
			this->listDep = (gcnew System::Windows::Forms::ListBox());
			this->tabCheckin = (gcnew System::Windows::Forms::TabPage());
			this->pnlLogin = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabClient->SuspendLayout();
			this->tabPackage->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabClient
			// 
			this->tabClient->Controls->Add(this->tabPackage);
			this->tabClient->Controls->Add(this->tabCheckin);
			this->tabClient->Location = System::Drawing::Point(0, 0);
			this->tabClient->Name = L"tabClient";
			this->tabClient->SelectedIndex = 0;
			this->tabClient->Size = System::Drawing::Size(580, 340);
			this->tabClient->TabIndex = 0;
			// 
			// tabPackage
			// 
			this->tabPackage->Controls->Add(this->button1);
			this->tabPackage->Controls->Add(this->btnDep);
			this->tabPackage->Controls->Add(this->btnExt);
			this->tabPackage->Controls->Add(this->listDep);
			this->tabPackage->Location = System::Drawing::Point(4, 22);
			this->tabPackage->Name = L"tabPackage";
			this->tabPackage->Padding = System::Windows::Forms::Padding(3);
			this->tabPackage->Size = System::Drawing::Size(572, 314);
			this->tabPackage->TabIndex = 0;
			this->tabPackage->Text = L"Packages";
			this->tabPackage->UseVisualStyleBackColor = true;
			// 
			// btnDep
			// 
			this->btnDep->Location = System::Drawing::Point(350, 43);
			this->btnDep->Name = L"btnDep";
			this->btnDep->Size = System::Drawing::Size(151, 23);
			this->btnDep->TabIndex = 4;
			this->btnDep->Text = L"Get Dependencies";
			this->btnDep->UseVisualStyleBackColor = true;
			this->btnDep->Click += gcnew System::EventHandler(this, &UserInterface::btnDep_Click);
			// 
			// btnExt
			// 
			this->btnExt->Location = System::Drawing::Point(350, 159);
			this->btnExt->Name = L"btnExt";
			this->btnExt->Size = System::Drawing::Size(151, 23);
			this->btnExt->TabIndex = 3;
			this->btnExt->Text = L"Extract File";
			this->btnExt->UseVisualStyleBackColor = true;
			this->btnExt->Click += gcnew System::EventHandler(this, &UserInterface::btnExt_Click);
			// 
			// listDep
			// 
			this->listDep->FormattingEnabled = true;
			this->listDep->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"..", L"*.*", L"Display"});
			this->listDep->Location = System::Drawing::Point(20, 20);
			this->listDep->Name = L"listDep";
			this->listDep->Size = System::Drawing::Size(292, 277);
			this->listDep->TabIndex = 0;
			// 
			// tabCheckin
			// 
			this->tabCheckin->Location = System::Drawing::Point(4, 22);
			this->tabCheckin->Name = L"tabCheckin";
			this->tabCheckin->Padding = System::Windows::Forms::Padding(3);
			this->tabCheckin->Size = System::Drawing::Size(572, 314);
			this->tabCheckin->TabIndex = 1;
			this->tabCheckin->Text = L"Checkin";
			this->tabCheckin->UseVisualStyleBackColor = true;
			// 
			// pnlLogin
			// 
			this->pnlLogin->Location = System::Drawing::Point(0, 0);
			this->pnlLogin->Name = L"pnlLogin";
			this->pnlLogin->Size = System::Drawing::Size(600, 370);
			this->pnlLogin->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(378, 226);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &UserInterface::button1_Click);
			// 
			// UserInterface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 362);
			this->Controls->Add(this->tabClient);
			this->Name = L"UserInterface";
			this->Text = L"UI";
			this->tabClient->ResumeLayout(false);
			this->tabPackage->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion


		System::Void btnDep_Click(System::Object^  sender, System::EventArgs^  e)
		{
			SendMessage(Ider::MsgType::Dependency);
		}

		System::Void btnExt_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			SendMessage(Ider::MsgType::File);
		}

		System::Collections::Generic::List<String^>^ selectionTrack;

		ICommunicator* sender;
		Ider::IMessageHandler* mh;
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 System::Collections::Generic::List<String^>^ packages
					 =gcnew System::Collections::Generic::List<String^>();
				 packages->Add(L"..");
				 packages->Add(L"*.*");
				 packages->Add(L"Hello");
				 packages->Add(L"Display");
				 ShowPackageListBox(packages);
			 }
};
}


#endif
