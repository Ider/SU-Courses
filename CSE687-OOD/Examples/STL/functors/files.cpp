/////////////////////////////////////////////////////////////////
//  files.cpp - demonstrate use of functor to control order    //
//              of an STL set holding fileInfo objects         //
//                                                             //
//  Jim Fawcett, CSE 687 - Object Oriented Design, Spring 2001 //
/////////////////////////////////////////////////////////////////

#pragma warning(disable : 4786)
#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include "fileInfo.h"
using namespace std;

//----< comparison functor >-----------------------------------

class compareFI {

  public:
    bool operator()(const fileInfo &fi1, const fileInfo &fi2);
};

bool compareFI::operator()(const fileInfo &fi1, const fileInfo &fi2) {

  return (fi1.later(fi2));
}

//----< test stub >--------------------------------------------

void main() {

  cout << "\n  Demonstrate Using Functor to Control Order of  "
       << "\n                fileInfo Objects                 "
       << "\n            in Associative Container             "
       << "\n ===============================================\n";

  cout << "\n  Compare by file time and date using functor "
       << "\n      based on fileInfo later(...) member     "
       << "\n ---------------------------------------------";

  set<fileInfo,compareFI> filesByDate;
  fileInfo getFile(".");

  if(getFile.firstFile("*.*"))
    filesByDate.insert(getFile);
  while(getFile.nextFile())
    filesByDate.insert(getFile);
  getFile.closeFile();

  set<fileInfo, compareFI>::iterator it;
  for(it = filesByDate.begin(); it != filesByDate.end(); it++)
    cout << "\n  " << setw(25) << it->name() 
                   << setw(12) << it->time() 
                   << setw(12) << it->date();
  cout << "\n\n";

//
  cout << "\n  Compare by file name using fileInfo operator<(...) "
       << "\n ----------------------------------------------------";

  set<fileInfo> filesByName;
  for(it = filesByDate.begin(); it != filesByDate.end(); it++)
    filesByName.insert(*it);

  set<fileInfo>::iterator nit;
  for(nit = filesByName.begin(); nit != filesByName.end(); nit++)
    cout << "\n  " << setw(25) << nit->name() 
                   << setw(12) << nit->time() 
                   << setw(12) << nit->date();
  cout << "\n\n";
}
