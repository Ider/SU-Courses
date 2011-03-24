/////////////////////////////////////////////////////////////////
// filebuf.cpp                                                 //
//   demonstrate low level input and output using streambufs   //
//   built from FILE pointer and stdout                        //
//                                                             //
// Jim Fawcett, 24 Mar 96, modified 23 Mar 97, 01 Mar 04       //
/////////////////////////////////////////////////////////////////

#include <iostream>    // cout, <<
#include <fstream>     // ifstream(), <<, >>
using namespace std;

//----< display titles >---------------------------------------

void title(const char *t, char ul = '-', ostream &out = cout) {

  int len = strlen(t) + 2;
  std::string line(len,ul);
  if(ul == '=')
    out << "\n " << line.c_str();
  out << "\n  " << t
      << "\n " << line.c_str() << endl;
}

//----< begin demonstration >----------------------------------

void main(int argc, char *argv[]) {

  //////////////////////////////////////////////////////////////
  title("Demonstrating use of Stream Buffers with File IO",'=');
  //////////////////////////////////////////////////////////////

  if(argc < 2) {
    cout << "\nplease enter name of text file on command line\n";
    exit(1);
  }

  title("using streambuf for input from file");
  /////////////////////////////////////////////

  filebuf ifb;                       // create filebuf
  ifb.open(argv[argc-1],ios::in);    // attach to file
  cout << &ifb << endl;              // stream to cout
  cout.flush();
//
  title("using streambuf for output to stdout");
  //////////////////////////////////////////////

  istream in(&ifb);            // make stream in, attached to ifb
  in.seekg(0);                 // move to top of input buffer
  ostream out(cout.rdbuf());   // make stream out, attached to cout streambuf
  out << &ifb << endl;         // stream it to out
  out.flush();

// could replace last statement with the lower level
// gets and puts shown below

  title("using low-level streambuf interface for output to stdout");
  //////////////////////////////////////////////////////////////////

  streambuf* pOfb = cout.rdbuf();
  in.seekg(0);
  char ch;
  while((ch = ifb.sbumpc()) != EOF)
    pOfb->sputc(ch);

  cout << "\n\n";
}
