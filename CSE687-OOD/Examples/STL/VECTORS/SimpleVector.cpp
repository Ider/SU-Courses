///////////////////////////////////////////////////////////////
//  SimpleVector.cpp - demonstrate basic vector operations   //
//                                                           //
//  Jim Fawcett, CSE687 Demonstration, Jan 2001              //
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
using namespace std;

//----< demonstrate simplest vector capabilities >-------------

void main() {

  cout << "\n  Demonstrate Simplest STL vector operations "
       << "\n ============================================\n\n";

  cout << "\n ----------------------------"
       << "\n  define a vector of strings "
       << "\n ----------------------------\n";

  vector< string > demo1;
  demo1.push_back("first string");
  demo1.push_back("second string");
  demo1.push_back("third string");
  
  int i;
  for(i=0; i<demo1.size(); i++)
    cout << "\n  " << demo1[i].c_str();
  cout << endl;

  cout << "\n ----------------------------"
       << "\n  define a vector of doubles "
       << "\n ----------------------------\n";
  
  vector< double > demo2;
  demo2.push_back(3.1415927);
  demo2.push_back(-3.5e-17);
  demo2.push_back(5.777e+30);
  
  for(i=0; i<demo2.size(); i++)
    cout << "\n  " << demo2[i];
  cout << "\n\n";
}
