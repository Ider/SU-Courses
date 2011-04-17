/////////////////////////////////////////////////////////////////////
// Command.cpp - Provides Interface and implements notifications   //
// ver 1.0                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Dimension 9200, Vista Ultimate              //
// Application:   Utility for CSE687 and CSE775 projects           //
// Author:        Jim Fawcett, Syracuse University, CST 4-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "command.h"

#ifdef TEST_COMMAND

class myCommand : public ICommand<const std::string&>
{
public:
  typedef void (myCommand::*EventHandler)(const std::string&);

  myCommand(EventHandler eh) : handler_(eh) {}
  void execute(const std::string& msg)
  {
    (this->*handler_)(msg);
  }
  void first_handler(const std::string& msg)
  {
    std::cout << "\n  in first_handler msg is: " << msg;
  }
  void second_handler(const std::string& msg)
  {
    std::cout << "\n  in second_handler msg is: " << msg;
  }
private:
  EventHandler handler_;
};

void main()
{
  std::cout << "\n  Testing Command Pattern ";
  std::cout << "\n =========================\n";

  myCommand cmd1(&myCommand::first_handler);
  myCommand cmd2(&myCommand::second_handler);
  Invoker<const std::string&> inv;
  inv.Register(&cmd1);
  inv.Register(&cmd2);
  inv.Invoke("first event");
  inv.Invoke("second event");
  std::cout << "\n\n";
}
#endif
