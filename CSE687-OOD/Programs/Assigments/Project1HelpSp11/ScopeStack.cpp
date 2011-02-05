///////////////////////////////////////////////////////////////////////////////
// ScopeStack.cpp - implements template stack holding items with two values  //
//                                                                           //
// version 2.0 - fixed bug in pop() method found by Drumil Bhattad           //
//                                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2011                 //
///////////////////////////////////////////////////////////////////////////////

//----< test stub >------------------------------------------------------

#ifdef TEST_SCOPESTACK

#include "ScopeStack.h"
#include <string>
#include <iostream>

typedef ScopeStack<std::string, std::string> stack;

int main()
{
  std::cout << "\n  Testing Scope Stack";
  std::cout << "\n =====================\n";

  std::cout << "\n  pushing items onto ScopeStack instance";
  std::cout << "\n ----------------------------------------";

  stack testStack;
  std::pair<std::string, std::string> item;

  item.first = "type1";
  item.second = "name1";
  testStack.push(item);

  item.first = "type2";
  item.second = "name2";
  testStack.push(item);

  item.first = "type3";
  item.second = "name3";
  testStack.push(item);

  showStack<std::string, std::string>(false);
  std::cout << std::endl;

  std::cout << "\n  pushing items onto ScopeStack with static methods";
  std::cout << "\n ---------------------------------------------------";

  item.first = "newtype1";
  item.second = "newname1";
  stack::push(item);

  item.first = "newtype2";
  item.second = "newname2";
  stack::push(item);

  item.first = "newtype3";
  item.second = "newname3";
  stack::push(item);

  showStack<std::string, std::string>(false);
  std::cout << std::endl;

  std::cout << "\n  Popping two items off ScopeStack";
  std::cout << "\n ----------------------------------";

  testStack.pop();
  stack::pop();

  showStack<std::string, std::string>(false);
  std::cout << "\n\n";
}

#endif
