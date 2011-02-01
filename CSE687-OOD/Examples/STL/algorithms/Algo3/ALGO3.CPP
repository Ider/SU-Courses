///////////////////////////////////////////////////////////////
//  algo2b.cpp - demonstrate generate algorithm on a semi-   //
//              useful application                           //
//                                                           //
//  Jim Fawcett, 4/5/98                                      //
///////////////////////////////////////////////////////////////

#include <iostream>     // cout
#include <strstream>    // ostrstream
#include <fstream>      // ifstream
#include <iomanip>      // setw(n)
#include <algorithm>    // copy, generate
#include <iterator>     // ostream_iterator
#include <list>       
#include <string>

#pragma warning(disable : 4786)

using namespace std;

/////////////////////////////////////////////////////////////
//  stringGen -- a string generator function               //
//               Reads an input stream, collecting lines   //
//               and prepending a line count.  It returns  //
//               the numbered line as a string.            //
/////////////////////////////////////////////////////////////

string stringGen(istream &in) {

  static count = 0;
    // capture line number and line text in a strstream
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

//
/////////////////////////////////////////////////////////////
//  strGen -- a function object                            //
//            Input stream is captured with constructor    //
//            and stored as a private member, nicely       //
//            encapsulated.  The operator() member now     //
//            serves as the generator function!            //
/////////////////////////////////////////////////////////////
            
class strGen {

  public:
    strGen(istream &in) : _in(in) { }
    string operator()() { return stringGen(_in); }
  private:
    istream &_in;
};

void main(int argc, char *argv[]) {

  ifstream in(argv[argc-1]);
  if(!in.good() || argc == 1) {
    cout << "  can't open file " << argv[argc-1] << endl;
    return;
  }
  
  /////////////////////////////////////////////////////
  // declare function object for use as a generator  //
  /////////////////////////////////////////////////////

  strGen sG(in);  

  /////////////////////////////////////////////////
  // store numbered lines in a list of strings   //
  /////////////////////////////////////////////////

  const int MAXLines = 1000;
  list<string> fileLines;

  try {
    generate_n(
      inserter(fileLines, fileLines.begin()),  // insert in list
      MAXLines,                                // line limit 
      sG                                       // invoke sG() 
    );
  }
  catch(char *msg) {
    cout << "\n  " << msg << endl;
  }

  /////////////////////////////////////
  //  send numbered lines to output  //
  /////////////////////////////////////

  ostream_iterator<string> outString(cout);
  copy(fileLines.begin(), fileLines.end(), outString);
}
