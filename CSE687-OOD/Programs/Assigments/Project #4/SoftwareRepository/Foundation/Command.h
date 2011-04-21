#ifndef COMMAND_H
#define COMMAND_H
/////////////////////////////////////////////////////////////////////
// Command.h - Provides Interface for and implements notifications //
// ver 1.0                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Dimension 9200, Vista Ultimate              //
// Application:   Utility for CSE687 and CSE775 projects           //
// Author:        Jim Fawcett, Syracuse University, CST 4-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
   Module Operations:
   ==================
   Defines ICommand interface and an Invoker of instances of classes
   derived from ICommands.  This notification model is called the 
   Command Pattern or Publish and Subscribe Pattern.  .Net Delegates
   are a somewhat more limited form of this pattern.

   Public Interface:
   =================
   class myCommand : public ICommand<const std::string&> { ... };
   myCommand cmd;
   Invoker.Register(&cmd);
   Invoker.Invoke("some arg");

   Required Files:
   ===============
   Command.h, Command.cpp

   Build Process:
   ==============
   cl /EHsc Command.cpp

   Maintenance History:
   ====================
   ver 1.0 : 29 Mar 08
   - first release

 */

#include <vector>
#include <string>

template <typename T>
class ICommand
{
public:
  virtual void execute(T t)=0;
  virtual ~ICommand() {}
};

template <typename T>
class Invoker
{
public:
  void Register(ICommand<T>* pCommand)
  {
    commands.push_back(pCommand);
  }
  void Invoke(T t)
  {
    std::vector<ICommand<T>*>::const_iterator iter;
    for(iter=commands.begin(); iter!=commands.end(); ++iter)
      (*iter)->execute(t);
  }
private:
  std::vector<ICommand<T>*> commands;
};

#endif
