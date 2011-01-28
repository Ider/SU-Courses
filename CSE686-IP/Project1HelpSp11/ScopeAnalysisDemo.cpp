/////////////////////////////////////////////////////////////////////
//  ScopeAnalysisDemo.cpp - demo recursive descent scope analysis  //
//  ver 1.1                                                        //
//                                                                 //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09                  //
//  Author:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "ScopeAnalysisDemo.h"

//---< is this token a keyword that will be followed by a paren? >---

bool isSpecialKey(const std::string& tok)
{
  const int KeyCount = 5;
  std::string SpecialKeys[KeyCount] = { "if", "for", "while", "switch", "catch" };
  for(int i=0; i<KeyCount; ++i)
    if(tok == SpecialKeys[i])
      return true;
  return false;
}
//----< show contents of stack >-------------------------------------

void scoper::showStack()
{
  // Since the stack hides its contents, you have to pop everything off,
  // see what it is, then push it back on.

  std::stack<std::string> temp;
  std::cout << "\n  scope stack: ";
  while(scopeStk.size() > 0)
  {
    temp.push(scopeStk.top());
    scopeStk.pop();
  }
  while(temp.size() > 0)
  {
    scopeStk.push(temp.top());
    std::cout << temp.top() << " ";
    temp.pop();
  }
}
//----< demonstrate scope analysis using scope stack >---------------

void scoper::walkScopes()
{
  // show the current contents of scope stack
  showStack();

  // start scope analysis
  std::string tok = "anonymous";
  while(se.get())
  {
    // show semiExpressions that change scope

    if(se.find("{") < se.length() || se.find("}") < se.length())
      std::cout << "\n" << se.show();
    
    std::string lastTok = se[se.length()-1];
    if(lastTok == "}")  // leaving current scope
    {
      scopeStk.pop();
      showStack();
      if(scopeStk.size() == 0)
        std::cout << "\n";  // puts space between global scope outputs
      return;
    }
    // The code below tries to capture the scope identifier.
    // Several special cases are not handled effectively, e.g.:
    // operator[](...), for(int i=0; i<Max; ++i) {, etc.
    // This is left as an exercise for the student.

    if(lastTok == "{")  // entering new scope
    {
      int len = se.find("(");
      if(len < se.length())  // ident(...) {
      {
        if(len > 0)
        {
          if(isSpecialKey(se[len-1])) 
            tok = se[len-1];           // some control structure, see note above.
          else
            tok = "function";
        }
        else
          tok = "anonymous";
        scopeStk.push(tok);
        walkScopes();
        continue;
      }
      if(se.length() > 2)  // class X {, enum T {, etc.
        tok = se[se.length()-3];
      else if(se.length() > 1)  // do {, catch {, etc.
        tok = se[se.length()-2];
      scopeStk.push(tok);
      walkScopes();
    }
  }
}
//----< show scope analysis using tokenizer and semiExpressions >----

int main(int argc, char* argv[])
{
  std::cout << "\n  Code Scope Analysis Demo\n "
            << std::string(26,'=') << std::endl;

  if(argc < 2)
  {
    std::cout 
      << "\n  please enter name of file to process on command line\n\n";
    return 1;
  }

  for(int i=1; i<argc; ++i)
  {
    std::cout << "\n  Processing file " << argv[i];
    std::cout << "\n  " << std::string(16 + strlen(argv[i]),'-') << "\n";
    try
    {
      std::cout << "\n  Walking code scopes in " << argv[i];
      std::cout << "\n  " << std::string(23 + strlen(argv[i]),'-') << "\n";
      Toker toker(argv[i]);
      toker.setMode(Toker::code);  // to parse XML, use toker.setMode(Toker::xml)
      SemiExp se(&toker);
      scoper sc(se);
      sc.walkScopes();
    }
    catch(std::exception ex)
    {
      std::cout << "\n  " << ex.what() << "\n\n";
    }
  }
}
