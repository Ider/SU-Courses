///////////////////////////////////////////////////////////////
//  vectors.cpp - demonstrate basic vector operations        //
//                                                           //
//  Jim Fawcett, ECS500 instructor, Su'99                    //
///////////////////////////////////////////////////////////////
//  STL vectors are implemented as expandable arrays.        //
//  This implies that for large vectors:                     //
//    - finding elements is always fast - random access      //
//    - inserting an element is fast only near the end       //
//    - deleting an element is fast only near the end        //
///////////////////////////////////////////////////////////////

#pragma warning(disable : 4786)
#include <vector>
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

  cout << "\n  Demonstrate basic STL vector operations "
       << "\n =========================================\n\n";

  cout << "\n  define a vector of strings "
       << "\n --------------------------\n";
  vector< string > up;
  up.push_back("first string");
  up.push_back("second string");
  up.push_back("third string");
  showCont< vector<string> >(up);

  cout << "\n -----------------------------------------"
       << "\n  define a new vector with reversed order "
       << "\n -----------------------------------------\n";
  vector< string > down;
  down.insert(down.begin(),"first string");
  down.insert(down.begin(),"second string");
  down.insert(down.begin(),"third string");
  showCont(down);    // note the alternate notation

//
  cout << "\n ------------------------------------------"
       << "\n  define a vector from an array of strings "
       << "\n ------------------------------------------\n";
  string sArr[5] = { "one", "two", "three", "four", "five" };
  vector<string> fromArr(&sArr[0],&sArr[5]);
  showCont(fromArr);
  cout << endl;

  cout << "\n ---------------------------------"
       << "\n  demonstrate finding and erasing "
       << "\n ---------------------------------\n";
  cout << "  value = \"three\"\n";
  vector<string>::iterator it;
  it = find(fromArr.begin(),fromArr.end(),"three");
  if(it != fromArr.end())
    fromArr.erase(it);
  showCont(fromArr);

  cout << "\n -----------------------------"
       << "\n  demonstrate erasing a range "
       << "\n -----------------------------\n";
  vector<string>::iterator it1, it2;
  it1 = fromArr.begin();
  it2 = fromArr.end();
  --it2; --it2;
  cout << "  range = [\"" << *it1 << "\", \"" << *it2 << "\")\n";
  fromArr.erase(it1,it2);
  showCont(fromArr);

  cout << endl;
}
