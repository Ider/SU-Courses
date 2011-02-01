///////////////////////////////////////////////////////////////
//  algo2.cpp - demonstrate generate algorithm on a semi-    //
//              useful application                           //
//                                                           //
//  Jim Fawcett, 4/5/98                                      //
///////////////////////////////////////////////////////////////

#include <iostream>
#include <strstream>
#include <fstream>
#include <iomanip>
#include <algorithm>    // fill, fill_n, copy, generate
#include <iterator>     // ostream_iterator
#include <list>
#include <string>

#pragma warning(disable : 4786)

using namespace std;

///////////////////////////////////////////////////////////
//  use this global because in Visual C++ generator must //
//  take no arguments, but stringGen needs access to the //
//  input stream -- will show alternative in next demo.  //
///////////////////////////////////////////////////////////
ifstream in;

string stringGen() {

  static count = 0;
  ostrstream temp;
  temp.flush();
  temp << setw(4) << count++ << ": ";
  const int MAX = 75;
  char buffer[MAX];
  if(!in.good())
    throw "finished processing file\n";
  in.getline(buffer,MAX);
  temp << buffer << '\n' << ends;
  return temp.str();
}

void main(int argc, char *argv[]) {

  in.open(argv[argc-1]);
  if(!in.good() || argc == 1) {
    cout << "  can't open file " << argv[argc-1] << endl;
    return;
  }
  
  const int MAXLines = 1000;
  list<string> fileLines;
  try {
    generate_n(
      inserter(fileLines, fileLines.begin()), 
      MAXLines, 
      stringGen 
    );
  }
  catch(char *msg) {
    cout << "\n  " << msg << endl;
  }
  ostream_iterator<string> outString(cout);
  copy(fileLines.begin(), fileLines.end(), outString);
}
