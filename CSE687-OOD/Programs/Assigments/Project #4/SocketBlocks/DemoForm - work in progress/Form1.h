#pragma once


namespace DemoForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
  using namespace System::IO;
  using namespace System::Threading;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::GroupBox^  groupBox1;
  private: System::Windows::Forms::GroupBox^  groupBox2;
  private: System::Windows::Forms::ListBox^  fileSendMsgs;
  private: System::Windows::Forms::ListBox^  selectFilesListBox;
  private: System::Windows::Forms::GroupBox^  groupBox3;
  private: System::Windows::Forms::Label^  label2;
  private: System::Windows::Forms::Label^  label1;
  private: System::Windows::Forms::Button^  listenButton;
  private: System::Windows::Forms::Button^  connectButton;
  private: System::Windows::Forms::TextBox^  localStatus;
  private: System::Windows::Forms::TextBox^  localPortText;
  private: System::Windows::Forms::TextBox^  remoteStatusText;
  private: System::Windows::Forms::TextBox^  remotePortText;
  private: System::Windows::Forms::TextBox^  localIPtext;
  private: System::Windows::Forms::TextBox^  remoteIPtext;
  private: System::Windows::Forms::ListBox^  msgListBox;
  private: System::Windows::Forms::Label^  label3;
  private: System::Windows::Forms::TextBox^  sourcePathText;
  private: System::Windows::Forms::Button^  msgSendButton;
  private: System::Windows::Forms::TextBox^  msgText;

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
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->msgSendButton = (gcnew System::Windows::Forms::Button());
      this->msgText = (gcnew System::Windows::Forms::TextBox());
      this->msgListBox = (gcnew System::Windows::Forms::ListBox());
      this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
      this->sourcePathText = (gcnew System::Windows::Forms::TextBox());
      this->fileSendMsgs = (gcnew System::Windows::Forms::ListBox());
      this->selectFilesListBox = (gcnew System::Windows::Forms::ListBox());
      this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->listenButton = (gcnew System::Windows::Forms::Button());
      this->connectButton = (gcnew System::Windows::Forms::Button());
      this->localStatus = (gcnew System::Windows::Forms::TextBox());
      this->localPortText = (gcnew System::Windows::Forms::TextBox());
      this->remoteStatusText = (gcnew System::Windows::Forms::TextBox());
      this->remotePortText = (gcnew System::Windows::Forms::TextBox());
      this->localIPtext = (gcnew System::Windows::Forms::TextBox());
      this->remoteIPtext = (gcnew System::Windows::Forms::TextBox());
      this->groupBox1->SuspendLayout();
      this->groupBox2->SuspendLayout();
      this->groupBox3->SuspendLayout();
      this->SuspendLayout();
      // 
      // groupBox1
      // 
      this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->groupBox1->Controls->Add(this->msgSendButton);
      this->groupBox1->Controls->Add(this->msgText);
      this->groupBox1->Controls->Add(this->msgListBox);
      this->groupBox1->Location = System::Drawing::Point(13, 254);
      this->groupBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Padding = System::Windows::Forms::Padding(4, 5, 4, 5);
      this->groupBox1->Size = System::Drawing::Size(711, 352);
      this->groupBox1->TabIndex = 0;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"Messages";
      // 
      // msgSendButton
      // 
      this->msgSendButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->msgSendButton->Location = System::Drawing::Point(17, 44);
      this->msgSendButton->Name = L"msgSendButton";
      this->msgSendButton->Size = System::Drawing::Size(75, 33);
      this->msgSendButton->TabIndex = 2;
      this->msgSendButton->Text = L"Send";
      this->msgSendButton->UseVisualStyleBackColor = true;
      this->msgSendButton->Click += gcnew System::EventHandler(this, &Form1::msgSendButton_Click);
      // 
      // msgText
      // 
      this->msgText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->msgText->Location = System::Drawing::Point(115, 48);
      this->msgText->Name = L"msgText";
      this->msgText->Size = System::Drawing::Size(589, 26);
      this->msgText->TabIndex = 1;
      // 
      // msgListBox
      // 
      this->msgListBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->msgListBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->msgListBox->FormattingEnabled = true;
      this->msgListBox->ItemHeight = 20;
      this->msgListBox->Location = System::Drawing::Point(7, 116);
      this->msgListBox->Name = L"msgListBox";
      this->msgListBox->Size = System::Drawing::Size(697, 224);
      this->msgListBox->TabIndex = 0;
      // 
      // groupBox2
      // 
      this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->groupBox2->Controls->Add(this->sourcePathText);
      this->groupBox2->Controls->Add(this->fileSendMsgs);
      this->groupBox2->Controls->Add(this->selectFilesListBox);
      this->groupBox2->Location = System::Drawing::Point(751, 4);
      this->groupBox2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
      this->groupBox2->Name = L"groupBox2";
      this->groupBox2->Padding = System::Windows::Forms::Padding(4, 5, 4, 5);
      this->groupBox2->Size = System::Drawing::Size(476, 602);
      this->groupBox2->TabIndex = 1;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = L"File Upload";
      // 
      // sourcePathText
      // 
      this->sourcePathText->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->sourcePathText->Location = System::Drawing::Point(8, 529);
      this->sourcePathText->Multiline = true;
      this->sourcePathText->Name = L"sourcePathText";
      this->sourcePathText->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
      this->sourcePathText->Size = System::Drawing::Size(461, 48);
      this->sourcePathText->TabIndex = 3;
      this->sourcePathText->WordWrap = false;
      this->sourcePathText->TextChanged += gcnew System::EventHandler(this, &Form1::sourcePath_TextChanged);
      // 
      // fileSendMsgs
      // 
      this->fileSendMsgs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->fileSendMsgs->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->fileSendMsgs->FormattingEnabled = true;
      this->fileSendMsgs->ItemHeight = 20;
      this->fileSendMsgs->Location = System::Drawing::Point(8, 27);
      this->fileSendMsgs->Name = L"fileSendMsgs";
      this->fileSendMsgs->Size = System::Drawing::Size(461, 84);
      this->fileSendMsgs->TabIndex = 2;
      // 
      // selectFilesListBox
      // 
      this->selectFilesListBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->selectFilesListBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->selectFilesListBox->FormattingEnabled = true;
      this->selectFilesListBox->ItemHeight = 20;
      this->selectFilesListBox->Location = System::Drawing::Point(7, 134);
      this->selectFilesListBox->Name = L"selectFilesListBox";
      this->selectFilesListBox->Size = System::Drawing::Size(462, 364);
      this->selectFilesListBox->TabIndex = 0;
      this->selectFilesListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::selectFilesListBox_SelectedIndexChanged);
      // 
      // groupBox3
      // 
      this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->groupBox3->Controls->Add(this->label3);
      this->groupBox3->Controls->Add(this->label2);
      this->groupBox3->Controls->Add(this->label1);
      this->groupBox3->Controls->Add(this->listenButton);
      this->groupBox3->Controls->Add(this->connectButton);
      this->groupBox3->Controls->Add(this->localStatus);
      this->groupBox3->Controls->Add(this->localPortText);
      this->groupBox3->Controls->Add(this->remoteStatusText);
      this->groupBox3->Controls->Add(this->remotePortText);
      this->groupBox3->Controls->Add(this->localIPtext);
      this->groupBox3->Controls->Add(this->remoteIPtext);
      this->groupBox3->Location = System::Drawing::Point(13, 4);
      this->groupBox3->Name = L"groupBox3";
      this->groupBox3->Size = System::Drawing::Size(711, 242);
      this->groupBox3->TabIndex = 2;
      this->groupBox3->TabStop = false;
      this->groupBox3->Text = L"Connection";
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label3->Location = System::Drawing::Point(552, 35);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(53, 20);
      this->label3->TabIndex = 2;
      this->label3->Text = L"status";
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label2->Location = System::Drawing::Point(395, 35);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(37, 20);
      this->label2->TabIndex = 2;
      this->label2->Text = L"port";
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(198, 35);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(85, 20);
      this->label1->TabIndex = 2;
      this->label1->Text = L"IP address";
      // 
      // listenButton
      // 
      this->listenButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->listenButton->Location = System::Drawing::Point(45, 165);
      this->listenButton->Name = L"listenButton";
      this->listenButton->Size = System::Drawing::Size(102, 40);
      this->listenButton->TabIndex = 1;
      this->listenButton->Text = L"listen";
      this->listenButton->UseVisualStyleBackColor = true;
      this->listenButton->Click += gcnew System::EventHandler(this, &Form1::listenButton_Click);
      // 
      // connectButton
      // 
      this->connectButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->connectButton->Location = System::Drawing::Point(45, 74);
      this->connectButton->Name = L"connectButton";
      this->connectButton->Size = System::Drawing::Size(102, 40);
      this->connectButton->TabIndex = 1;
      this->connectButton->Text = L"connect";
      this->connectButton->UseVisualStyleBackColor = true;
      this->connectButton->Click += gcnew System::EventHandler(this, &Form1::connectButton_Click);
      // 
      // localStatus
      // 
      this->localStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->localStatus->Location = System::Drawing::Point(527, 170);
      this->localStatus->Name = L"localStatus";
      this->localStatus->Size = System::Drawing::Size(111, 26);
      this->localStatus->TabIndex = 0;
      // 
      // localPortText
      // 
      this->localPortText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->localPortText->Location = System::Drawing::Point(372, 170);
      this->localPortText->Name = L"localPortText";
      this->localPortText->Size = System::Drawing::Size(111, 26);
      this->localPortText->TabIndex = 0;
      // 
      // remoteStatusText
      // 
      this->remoteStatusText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->remoteStatusText->Location = System::Drawing::Point(527, 79);
      this->remoteStatusText->Name = L"remoteStatusText";
      this->remoteStatusText->Size = System::Drawing::Size(111, 26);
      this->remoteStatusText->TabIndex = 0;
      // 
      // remotePortText
      // 
      this->remotePortText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->remotePortText->Location = System::Drawing::Point(372, 79);
      this->remotePortText->Name = L"remotePortText";
      this->remotePortText->Size = System::Drawing::Size(111, 26);
      this->remotePortText->TabIndex = 0;
      // 
      // localIPtext
      // 
      this->localIPtext->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->localIPtext->Location = System::Drawing::Point(178, 170);
      this->localIPtext->Name = L"localIPtext";
      this->localIPtext->ReadOnly = true;
      this->localIPtext->Size = System::Drawing::Size(154, 26);
      this->localIPtext->TabIndex = 0;
      // 
      // remoteIPtext
      // 
      this->remoteIPtext->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->remoteIPtext->Location = System::Drawing::Point(178, 79);
      this->remoteIPtext->Name = L"remoteIPtext";
      this->remoteIPtext->Size = System::Drawing::Size(154, 26);
      this->remoteIPtext->TabIndex = 0;
      // 
      // Form1
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(10, 20);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1247, 625);
      this->Controls->Add(this->groupBox3);
      this->Controls->Add(this->groupBox2);
      this->Controls->Add(this->groupBox1);
      this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
      this->Name = L"Form1";
      this->Text = L"Form1";
      this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
      this->groupBox1->ResumeLayout(false);
      this->groupBox1->PerformLayout();
      this->groupBox2->ResumeLayout(false);
      this->groupBox2->PerformLayout();
      this->groupBox3->ResumeLayout(false);
      this->groupBox3->PerformLayout();
      this->ResumeLayout(false);

    }
#pragma endregion
  private: 

    System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
    {
      sourcePathText->Text = Directory::GetCurrentDirectory();
      remoteIPtext->Text = "127.0.0.1";
      remotePortText->Text = "8080";
      localIPtext->Text = "127.0.0.1";
      localPortText->Text = "8081";
      String^ path = sourcePathText->Text;
      array<String^>^ files;
      if(Directory::Exists(path))
        files = Directory::GetFiles(path);
      else
      {
        selectFilesListBox->Items->Add("no files");
        return;
      }
      for each(String^ file in files)
      {
        String^ name = Path::GetFileName(file);
        selectFilesListBox->Items->Add(name);
      }
      String^ ip = localIPtext->Text;
      int port = Convert::ToInt32(localPortText->Text);
      //SetUpComm(ip,port);
    }
  private: 
    System::Void connectButton_Click(System::Object^  sender, System::EventArgs^  e) 
    {
    }
  private: 
    System::Void listenButton_Click(System::Object^  sender, System::EventArgs^  e) 
    {
    }
  private: 
    System::Void fileSelectButton_Click(System::Object^  sender, System::EventArgs^  e) 
    {
      for each(String^ file in files)
      {
        String^ name = Path::GetFileName(file);
        fileSendMsgs->Items->Insert(0,name);
        Invalidate();
        Thread::Sleep(100);
      }
    }
  private: 
    System::Void selectFilesListBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
    {
      String^ name = (String^)selectFilesListBox->SelectedItem;
      fileSendMsgs->Items->Insert(0,name);
    }
  private: 
    System::Void sourcePath_TextChanged(System::Object^  sender, System::EventArgs^  e) 
    {
      selectFilesListBox->Items->Clear();
      String^ path = sourcePathText->Text;
      if(Directory::Exists(path))
        files = Directory::GetFiles(path);
      else
      {
        selectFilesListBox->Items->Add("no files");
        return;
      }
      for each(String^ file in files)
      {
        String^ name = Path::GetFileName(file);
        selectFilesListBox->Items->Add(name);
      }
    }
  private:
    array<String^>^ files;
  private: 
    System::Void msgSendButton_Click(System::Object^  sender, System::EventArgs^  e) 
    {
      String^ msg = msgText->Text;
      msgListBox->Items->Insert(0,msg);
    }
};
}

