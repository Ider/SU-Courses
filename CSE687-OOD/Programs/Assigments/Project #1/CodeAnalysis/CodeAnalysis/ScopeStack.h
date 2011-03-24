#ifndef SCOPESTACK_H
#define SCOPESTACK_H
/////////////////////////////////////////////////////////////////////////////
// ScopeStack.h - implements template stack holding items with two values  //
//                                                                         //
// version 2.0 - fixed bug in pop() method found by Drumil Bhattad         //
//                                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2011               //
/////////////////////////////////////////////////////////////////////////////

#include <list>

template<typename T, typename N>
class ScopeStack {
public:
  typename typedef std::list< std::pair<T,N> >::iterator iterator;
  static void push(const std::pair<T,N>& item);
  static std::pair<T,N> pop();
  static size_t size();
  static iterator begin();
  static iterator end();
private:
  static std::list< std::pair<T,N> > stack;
};
template<typename T, typename N>
std::list< std::pair<T,N> > ScopeStack<typename T, typename N>::stack;

template<typename T, typename N>
typename inline size_t ScopeStack<T,N>::size() { return stack.size(); }

template<typename T, typename N>
typename inline ScopeStack<T,N>::iterator ScopeStack<T,N>::begin() { return stack.begin(); }

template<typename T, typename N>
typename inline ScopeStack<T,N>::iterator ScopeStack<T,N>::end() { return stack.end(); }

template<typename T, typename N>
void ScopeStack<T,N>::push(const std::pair<T,N>& item)
{
  stack.push_back(item);
}

template<typename T, typename N>
std::pair<T,N> ScopeStack<T,N>::pop() 
{ 
  std::pair<T,N> item = stack.back(); 
  stack.pop_back(); 
  return item; 
}

template<typename T, typename N>
void showStack(bool indent=true)
{
  if(ScopeStack<T,N>::size() == 0)
  {
    std::cout << "\n  ScopeStack is empty";
    return;
  }
  ScopeStack<T,N>::iterator iter = ScopeStack<T,N>::begin();
  while(iter != ScopeStack<T,N>::end())
  {
    std::string strIndent = std::string(2*ScopeStack<T,N>::size(),' ');
    if(!indent)
      strIndent = "";
    std::cout << "\n  " << strIndent << "(" << (*iter).first;
    std::cout << ", " << (*iter).second << ")";
    ++iter;
  }
}
#endif
