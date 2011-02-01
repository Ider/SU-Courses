/////////////////////////////////////////////////////////////////////
// CopyAndAssign.cpp - demonstrate container copy and assignment

#include <vector>
#include <list>
#include <set>
#include <string>
#include <iostream>
#include <algorithm>

template <typename C>
void showCon(const C& c, const std::string& msg)
{
  std::cout << "\n  " << msg;
  std::cout << "\n " << std::string(msg.size()+2,'-') << "\n  ";
  C::const_iterator iter;
  for(iter=c.begin(); iter!=c.end(); ++iter)
    std::cout << *iter << " ";
  std::cout << "\n\n";
}
void main()
{
  std::cout << "\n  Demonstrate Container Copy and Assignment";
  std::cout << "\n ===========================================\n";

  std::string animals[] 
    = { "ardvarrk", "platypus", "owl", "mule", "ox", "panther" };
  std::vector<std::string> vofa(&animals[0],&animals[6]);
  showCon(vofa,"Vector of Animals");

  std::vector<std::string> copy = vofa;
  showCon(copy,"Copy of Vector of Animals");

  std::vector<std::string> empty;
  empty = vofa;
  showCon(empty,"Empty after Assignment from Vector of Animals");

  std::list<std::string> lofa(vofa.begin(), vofa.end());
  showCon(lofa,"list copy constructed from vector");

  std::list<std::string> emptyList;
  std::copy(vofa.begin(), vofa.end(), back_inserter(emptyList));
  showCon(
    emptyList,
    "List is Copy of Vector using Copy Algorithm with back_inserter"
  );

  emptyList.clear();
  std::copy(vofa.begin(), vofa.end(), front_inserter(emptyList));
  showCon(
    emptyList,"List is Copy of Vector using Copy Algorithm with front_inserter"
  );
}