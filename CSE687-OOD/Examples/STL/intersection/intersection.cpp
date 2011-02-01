/////////////////////////////////////////////////////////////////
// intersection.cpp - find intersection of two sets            //
//                                                             //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005   //
/////////////////////////////////////////////////////////////////
// Intersection code derived from:
//   Designing Components with the C++ STL, Revised Edition
//   Ulrich Breymann, Addison-Wesley, 2000

#include <algorithm>
#include <set>
#include <string>
#include <iostream>

template <typename T>
struct showEach
{
  void operator()(const T& t) const { std::cout << t << " "; }
};

template <class C>
void show(const C& c)
{
  std::cout << "\n    ";
  for_each(c.begin(), c.end(),showEach<C::value_type>());
  std::cout << "\n";
}

template <class setType>
void intersection(const setType& s1, const setType& s2, setType& common)
{
  setType temp;
  typename setType::const_iterator it1 = s1.begin(), it2;

  while(it1 != s1.end())
  {
    it2 = s2.find(*it1++);  // uses set's find
    if(it2 != s2.end())
      temp.insert(*it2);
  }
  temp.swap(common);
}

//
void main()
{
  std:: cout << "\n  Demonstrating Set Intersection "
             << "\n ================================\n";

  std::string animals[5] = 
  { 
    "aardvark", "platypus", "owl", "snake", "man" 
  };
  std::string legsNoWings[6] = 
  { 
    "aardvark", "platypus", "man", "zebra", "elephant", "mule" 
  };

  typedef std::set<std::string> stringSet;

  stringSet Animals(&animals[0],&animals[5]);
  stringSet LegsNoWings(&legsNoWings[0],&legsNoWings[6]);
  stringSet result;

  std::cout << "\n  Show input sets "
            << "\n -----------------\n";
  show(Animals);
  show(LegsNoWings);

  intersection(Animals,LegsNoWings,result);

  std::cout << "\n  Show set intersection "
            << "\n -----------------------\n";
  show(result);

  std::cout << "\n\n";
}
