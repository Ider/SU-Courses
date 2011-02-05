///////////////////////////////////////////////////////////////////////////////
// ScopeStackTest.cpp - demo of template stack holding items with two values //
//                                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2011                 //
///////////////////////////////////////////////////////////////////////////////

#include "ScopeStack.h"
#include "SemiExpression.h"
#include "Tokenizer.h"

bool isSpecialKeyWord(const std::string& tok)
{
  const static std::string keys[]
    = { "for", "while", "switch", "if", "catch" };
  for(int i=0; i<5; ++i)
    if(tok == keys[i])
      return true;
  return false;
}

int main(int argc, char* argv[])
{
  typedef ScopeStack<std::string, std::string> Stack;
  typedef std::pair<std::string, std::string> StackItem;

  std::cout << "\n  Demonstrating Scope Analysis\n "
            << std::string(30,'=') << std::endl;
  if(argc < 2)
  {
    std::cout 
      << "\n  please enter name of file to process on command line\n\n";
    return 1;
  }

  for(int i=1; i<argc; ++i)
  {
    std::cout << "\n  Processing file " << argv[i];
    std::cout << "\n  " << std::string(16 + strlen(argv[i]),'-');
    try
    {
  	  Toker toker(argv[i]);
      SemiExp se(&toker);
      while(se.get())
      {
        if(se.length() < 1)
          continue;
        //std::cout << se.show().c_str() << std::endl;
        if(se[se.length() - 1] == "}")
        {
          Stack::pop();
          showStack<std::string, std::string>();
        }
        if(se.length() < 3)
          continue;
        if(se[se.length() - 1] == "{")
        {
          StackItem item;
          int pos = se.find("(");
          if(pos < se.length())
          {
            if(isSpecialKeyWord(se[pos-1]))
              item.first = "control";
            else
              item.first = "function";
            item.second = se[pos-1];
            Stack::push(item);
            showStack<std::string, std::string>();
          }
          else
          {
            item.first = se[se.length()-3];
            item.second = se[se.length()-2];
            Stack::push(item);
            showStack<std::string, std::string>();
          }
        }
      }
      std::cout << "\n\n";
    }
    catch(std::exception ex)
    {
      std::cout << "\n  " << ex.what() << "\n\n";
    }
  }
}
