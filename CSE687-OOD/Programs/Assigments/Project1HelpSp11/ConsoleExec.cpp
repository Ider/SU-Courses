/////////////////////////////////////////////////////////////////////
//  ConsoleExec.cpp - Demonstrates parsing                         //
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
  This module defines a console executive.  Its purpose is to provide
  a placeholder for command-line driven programs, like anal.  

  Public Interface:
  =================
  This Executive module provides services, not through a software
  interface, but through a set of command-line arguments,
  provided to allow a user to control the files analyzed and see
  the results of that analysis.

  Build Process:
  ==============
  Required files
    - ConsoleExec.cpp,
      ConfigureParser.h, ConfigureParser.cpp,
      ActionsAndRules.h, ActionsAndRules.cpp,
      Parser.h, Parser.cpp,
      SemiExpression.h, SemiExpression.cpp,
      tokenizer.h, tokenizer.cpp

  Build commands (either one)
    - devenv Project1HelpS06.sln
    - cl /EHsc ConsoleExec.cpp, ConfigureParser.cpp, ActionsAndRules.cpp \
               Parser.cpp SemiExpression.cpp Tokenizer.cpp

  Maintenance History:
  ====================
  ver 1.0 : 01 Feb 06
  - first release

*/

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include "Tokenizer.h"
#include "SemiExpression.h"
#include "Parser.h"
#include "ActionsAndRules.h"
#include "ConfigureParser.h"
//

int main(int argc, char* argv[])
{
  std::cout << "\n  Testing ConsoleExec Module\n "
            << std::string(28,'=') << std::endl;

  // collecting tokens from files, named on the command line

  if(argc < 2)
  {
    std::cout 
      << "\n  please enter name of file to process on command line\n\n";
    return 1;
  }

  for(int i=1; i<argc; ++i)
  {
    std::cout << "\n  Processing file " << argv[i];
    std::cout << "\n  " << std::string(22 + strlen(argv[i]),'-');

    ConfigParseToConsole configure;
    Parser* pParser = configure.Build();
    try
    {
      if(pParser)
      {
        if(!configure.Attach(argv[i]))
        {
          std::cout << "\n  could not open file " << argv[i] << std::endl;
          continue;
        }
      }
      else
      {
        std::cout << "\n\n  Parser not built\n\n";
        return 1;
      }
      // now that parser is built, use it

      while(pParser->next())
        pParser->parse();
      std::cout << "\n\n";
    }
    catch(std::exception& ex)
    {
      std::cout << "\n\n    " << ex.what() << "\n\n";
    }

//
    std::cout << "\n  Processing file for Queued Outputs " << argv[i];
    std::cout << "\n  " << std::string(35 + strlen(argv[i]),'-');

    ConfigParseToQueue Qconfigure;
    pParser = Qconfigure.Build();
    try
    {
      if(pParser)
      {
        if(!Qconfigure.Attach(argv[i]))
        {
          std::cout << "\n  could not open file " << argv[i] << std::endl;
          continue;
        }
      }
      else
      {
        std::cout << "\n\n  Parser not built\n\n";
        return 1;
      }
      // now that parser is built, use it

      while(pParser->next())
        pParser->parse();
      std::cout << "\n\n";
    }
    catch(std::exception& ex)
    {
      std::cout << "\n\n    " << ex.what() << "\n\n";
    }
    std::queue<std::string>* pQueue = Qconfigure.GetQueue();
    size_t len = pQueue->size();
    for(size_t i=0; i<len; ++i)
    {
      std::cout << "\n  " << pQueue->front();
      pQueue->pop();
    }
    std::cout << "\n\n";
  }
}
