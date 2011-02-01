///////////////////////////////////////////////////////////////
//  lists.cpp - demonstrate basic list operations            //
//                                                           //
//  Jim Fawcett, ECS500 instructor, Su'99                    //
///////////////////////////////////////////////////////////////
//  STL lists are implemented as doubly linked lists.        //
//  This implies that for large lists:                       //
//    - finding an interior element is slow                  //
//    - inserting an element is fast once the element to     //
//      insert in front of is found                          //
//    - deleting an element is fast once found               //
//    - adding or deleting from either end is fast           //
///////////////////////////////////////////////////////////////

#pragma warning(disable : 4786)
#include <list>
#include <string>
#include <iostream>
#include <algorithm>    // find()
using namespace std;

//----< generic function to display container contents >-------

template <class T>
void showCont(const T &cont) {

  cout << "  size of container = " << cont.size() << endl;
  T::const_iterator it;
  for(it = cont.begin(); it != cont.end(); it++)
    cout << "    " << *it << endl;
}

//----< demonstrate list capabilities >------------------------

void main() {

  cout << "\n  Demonstrate basic STL List operations "
       << "\n =======================================\n\n";

  cout << "\n  define a list of strings "
       << "\n --------------------------\n";
  list< string > up;
  up.insert(up.end(),"first string");
  up.insert(up.end(),"second string");
  up.insert(up.end(),"third string");
  showCont< list<string> >(up);

  cout << "\n ---------------------------------------"
       << "\n  define a new list with reversed order "
       << "\n ---------------------------------------\n";
  list< string > down;
  down.push_front("first string");
  down.push_front("second string");
  down.push_front("third string");
  showCont(down);    // note the alternate notation

//
  cout << "\n ---------------------------------------"
       << "\n  define a list from an array of strings "
       << "\n ---------------------------------------\n";
  string sArr[5] = { "one", "two", "three", "four", "five" };
  list<string> fromArr(&sArr[0],&sArr[5]);
  showCont(fromArr);
  cout << endl;

  cout << "\n ---------------------------------------"
       << "\n  demonstrate finding and erasing "
       << "\n ---------------------------------\n";
  cout << "  value = \"three\"\n";
  list<string>::iterator it;
  it = find(fromArr.begin(),fromArr.end(),"three");
  if(it != fromArr.end())
    fromArr.erase(it);
  showCont(fromArr);

  cout << "\n ---------------------------------------"
       << "\n  demonstrate erasing a range "
       << "\n -----------------------------\n";
  list<string>::iterator it1, it2;
  it1 = fromArr.begin();
  it2 = fromArr.end();
  --it2; --it2;
  cout << "  range = [\"" << *it1 << "\", \"" << *it2 << "\")\n";
  fromArr.erase(it1,it2);
  showCont(fromArr);

  cout << endl;
}
