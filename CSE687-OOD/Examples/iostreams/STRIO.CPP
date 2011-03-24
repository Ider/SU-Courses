///////////////////////////////////////////////////////////////
// strio.cpp - demonstrate stringstreams                     //
//                                                           //
// Jim Fawcett, 24 Mar 96, modified 04 Mar 02                //
///////////////////////////////////////////////////////////////

#include <iostream>     // cout, <<
#include <sstream>      // istringstream(), ostringstream(), <<, >>
#include <string>

using namespace std;

//----< display titles >---------------------------------------

void title(const char *t, char ul = '-', ostream &out = cout) {

  int len = strlen(t) + 2;
  string line(len,ul);
  if(ul == '=')
    out << "\n " << line;
  out << "\n  " << t
      << "\n " << line << endl;
}

//----< begin demonstration >----------------------------------

void main() {

  ///////////////////////////////////////////////////
  title("Demonstrating stringstream operations",'=');
  ///////////////////////////////////////////////////

  title("reading from istringstream");
  /////////////////////////////

  istringstream source("15 3.1415927 Now is the hour");
  cout << "\n  " << source.str() << endl;

  title("writing to ostringstream");
  ////////////////////////////////////

  ostringstream destin;
  destin << source.str();
  stringbuf *pStringBuf = destin.rdbuf();
  cout << "\n--source-----" << source.str();
  cout << "\n--destin-----" << destin.str();
  cout << "\n--stringBuf--" << pStringBuf->str() << endl;

//

  title("writing to custom buffer no longer supported in ostringstream");
  ///////////////////////////////////////////////////////////////////////

  title("parsing input buffer");
  //////////////////////////////

  int i;
  const int bufSize=50; 
  double d; 
  char savebuf[bufSize];
  
  source.seekg(0);
  source >> i >> d;
  cout << endl;
  cout << "  i = " << i << endl;
  cout << "  d = " << d << endl;
  int j;

  // The following operation is dangerous!
  //   extraction writes whole word into buffer,
  //   even if word size is larger than buffer

  for(j=0; j<4; j++) {
    source >> savebuf;
    cout << "  savebuf = " << savebuf << endl;
  }

  // Here is a saver, though less convenient way
  // to read strings from a stream

  title("safe parsing using destination string");
  ///////////////////////////////////////////////

  source.clear();
  source.seekg(0);
  string temp;
  while(source.good()) {
    source >> temp;
    cout << "\n  " << temp;
  }
  cout << "\n\n";

  title("char-by-char parsing");
  //////////////////////////////

  source.clear();
  source.seekg(0);
  temp = "";
  while(source.good()) {
    char ch = source.get();
    if(!isspace(ch))
      temp += ch;
    else if(temp.size() > 0) {
      cout << "\n  " << temp.c_str();
      temp = "";
    }
  }
  if(temp.size() > 0)
    cout << "\n  " << temp.c_str();
  cout << "\n\n";
}
