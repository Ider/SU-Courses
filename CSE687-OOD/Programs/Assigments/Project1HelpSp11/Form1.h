#pragma once
/////////////////////////////////////////////////////////////////////
//  Form1.h - Displays analyses of C++ language constructs         //
//                                                                 //
//  Lanaguage:     Visual C++ 2005                                 //
//  Platform:      Dell Dimension 9150, Windows XP SP2             //
//  Application:   Prototype for CSE687 Pr1, Sp06                  //
//  Author:        Jim Fawcett, CST 2-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module defines a Form that displays grammatical constructs
  from a selected C++ source file.  It uses the services of four other
  modules:
  - Parser is responsible for identifying and reporting specific
    grammatical constructs.  It does this by collecting a sequence of
    tokens, called a semi-expression, from a source file, and analyzing
    that with a set of rules.  Any rule that succeeds generates some
    kind of output by means of one or more associated actions.
  - ActionsAndRules is provided to support addition of parsing actions,
    and rules not provided by the reusable Parser module.
  - SemiExpression is responsible for collecting a set of tokens for
    Parser to analyze.  It is SemiExpression's job to return just the
    right amount of information for each parsing analysis.
  - Tokenizer provides a stream of tokens (words) extracted from a
    source code file by throwing away all whitespace except for new
    lines, and separating indentifier characters from punctuation.

  Public Interface:
  =================
  This Executive module provides services, not through a software
  interface, but through a set of controls provided on a form,
  provided to allow a user to control the files analyzed and see
  the results of that analysis.

  Build Process:
  ==============
  Required files
    - Executive.cpp, Parser.h, Parser.cpp, DerivedActions.h,
      SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp
  Build commands (either one)
    - devenv Project1HelpS06.sln

  Maintenance History:
  ====================
  ver 1.0 : 12 Jan 06
  - first release

*/
//
#include "../Tokenizer.h"
#include "../SemiExpression.h"
#include "../Parser.h"
#include "../ActionsAndRules.h"
#include "../ConfigureParser.h"

namespace Executive {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;
  using namespace System::IO;
  using namespace System::Text;

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
    }

  protected:

    ~Form1()
    {
      if (components)
      {
        delete components;
      }
    }
  protected: 
    private: System::Windows::Forms::Button^  button1;
    private: System::Windows::Forms::TextBox^  textBox1;
    private: System::Windows::Forms::ListBox^  listBox1;
    private: System::Windows::Forms::Button^  button2;
    private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
    private: System::Windows::Forms::TextBox^  textBox2;
    private: System::Windows::Forms::StatusStrip^  statusStrip1;
  private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;

  private:
    System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
      this->button1 = (gcnew System::Windows::Forms::Button());
      this->textBox1 = (gcnew System::Windows::Forms::TextBox());
      this->listBox1 = (gcnew System::Windows::Forms::ListBox());
      this->button2 = (gcnew System::Windows::Forms::Button());
      this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
      this->textBox2 = (gcnew System::Windows::Forms::TextBox());
      this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
      this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
      this->statusStrip1->SuspendLayout();
      this->SuspendLayout();
      // 
      // button1
      // 
      this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->button1->Location = System::Drawing::Point(493, 147);
      this->button1->Name = L"button1";
      this->button1->Size = System::Drawing::Size(62, 57);
      this->button1->TabIndex = 0;
      this->button1->Text = L"Analyze File";
      this->button1->UseVisualStyleBackColor = true;
      this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
      // 
      // textBox1
      // 
      this->textBox1->AcceptsReturn = true;
      this->textBox1->AcceptsTab = true;
      this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->textBox1->Location = System::Drawing::Point(54, 227);
      this->textBox1->Multiline = true;
      this->textBox1->Name = L"textBox1";
      this->textBox1->ReadOnly = true;
      this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
      this->textBox1->Size = System::Drawing::Size(501, 256);
      this->textBox1->TabIndex = 1;
      // 
      // listBox1
      // 
      this->listBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->listBox1->FormattingEnabled = true;
      this->listBox1->Location = System::Drawing::Point(54, 83);
      this->listBox1->Name = L"listBox1";
      this->listBox1->Size = System::Drawing::Size(420, 121);
      this->listBox1->TabIndex = 2;
      // 
      // button2
      // 
      this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->button2->Location = System::Drawing::Point(493, 83);
      this->button2->Name = L"button2";
      this->button2->Size = System::Drawing::Size(62, 47);
      this->button2->TabIndex = 0;
      this->button2->Text = L"Select Folder";
      this->button2->UseVisualStyleBackColor = true;
      this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
      // 
      // textBox2
      // 
      this->textBox2->Location = System::Drawing::Point(54, 35);
      this->textBox2->Name = L"textBox2";
      this->textBox2->Size = System::Drawing::Size(420, 20);
      this->textBox2->TabIndex = 3;
      // 
      // statusStrip1
      // 
      this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripStatusLabel1});
      this->statusStrip1->Location = System::Drawing::Point(0, 519);
      this->statusStrip1->Name = L"statusStrip1";
      this->statusStrip1->Size = System::Drawing::Size(596, 22);
      this->statusStrip1->TabIndex = 4;
      this->statusStrip1->Text = L"statusStrip1";
      // 
      // toolStripStatusLabel1
      // 
      this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
      this->toolStripStatusLabel1->Size = System::Drawing::Size(109, 17);
      this->toolStripStatusLabel1->Text = L"toolStripStatusLabel1";
      // 
      // Form1
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(596, 541);
      this->Controls->Add(this->statusStrip1);
      this->Controls->Add(this->textBox2);
      this->Controls->Add(this->listBox1);
      this->Controls->Add(this->textBox1);
      this->Controls->Add(this->button2);
      this->Controls->Add(this->button1);
      this->Name = L"Form1";
      this->Text = L"Form1";
      this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
      this->statusStrip1->ResumeLayout(false);
      this->statusStrip1->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
//
  private: 
    //----< browse button click handler >----------------------------

    System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
    {
      // set up folder browsing dialog

      folderBrowserDialog1 = gcnew FolderBrowserDialog(); 
      folderBrowserDialog1->SelectedPath = Directory::GetCurrentDirectory();

      // open browse dialog and process result

      System::Windows::Forms::DialogResult result
        = folderBrowserDialog1->ShowDialog();
      if(result == System::Windows::Forms::DialogResult::OK)
        textBox2->Text = folderBrowserDialog1->SelectedPath;

      // get a list of files in the folder

      array<String^>^ Files
        = Directory::GetFiles(folderBrowserDialog1->SelectedPath);

      // filter the list and put into the Form's ListBox

      listBox1->Items->Clear();
      for(int i=0; i<Files->Length; ++i)
      {
        String^ pExt = Path::GetExtension(Files[i]);
        if(pExt->IndexOf(L".cpp") != -1)
          listBox1->Items->Add(Files[i]);
        if(pExt->IndexOf(L".h") != -1)
          listBox1->Items->Add(Files[i]);
      }
    }
  private:
    //----< Form load handler >--------------------------------------

    System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
    {
      this->Text = "Parsing Prototype - Executive Form";
      toolStripStatusLabel1->Text = "Status normal";
    }
//
  private:
    //----< analyze button click handler >---------------------------

    System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
    {
      // extract path of the ListBox's selected file

      std::string* pString = new std::string();
      String^ lbSel;
      try
      {
        lbSel = listBox1->SelectedItem->ToString();
      }
      catch(System::Exception^ /*ex*/)
      {
        toolStripStatusLabel1->Text = L"Please select a file";
        return;
      }
      toolStripStatusLabel1->Text = lbSel;
      for(int i=0; i<lbSel->Length; ++i)
        pString->append(1,(char)lbSel[i]);

      DisplayAnalysis(pString);
    }
//
    //----< display analysis in TextBox >----------------------------

    System::Void DisplayAnalysis(std::string* pString)
    {
      ConfigParseToQueue Qconfigure;
      Parser* pParser = Qconfigure.Build();
           
      try
      {
        if(pParser)
        {
          if(!Qconfigure.Attach(*pString))
          {
          //  write this to status bar 
            std::string tmp = "could not open file ";
            tmp += *pString;
            toolStripStatusLabel1->Text = gcnew String(tmp.c_str());
            return;
          }
        }
        else
        {
          // write this to status bar
          toolStripStatusLabel1->Text = "Parser not built";
          return;
        }
        // now that parser is built, use it

        while(pParser->next())
          pParser->parse();
      }
      catch(std::exception& ex)
      {
        // write this to status bar
        toolStripStatusLabel1->Text = gcnew String(ex.what());
      }
      std::queue<std::string>* pQueue = Qconfigure.GetQueue();

      // put queue contents into Form's results text box

      StringBuilder^ tempStr = gcnew StringBuilder();
      textBox1->Text = "";
      int len = pQueue->size();
      for(int i=0; i<len; ++i)
      {
        int argLen = pQueue->front().size();
        for(int j=0; j<argLen; ++j)
          tempStr->Append((wchar_t)pQueue->front()[j]);
        textBox1->Text = textBox1->Text + tempStr->ToString() + "\r\n";
        pQueue->pop();
        tempStr->Remove(0,tempStr->Length);
      }
    }
  };
}

