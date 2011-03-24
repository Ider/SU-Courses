///////////////////////////////////////////////////////////////
// readwrit.cpp - demonstrate read/write fstreams            //
//                with buffer location seeking               //
// Jim Fawcett, 24 Mar 96, modified 23 Mar 97                //
///////////////////////////////////////////////////////////////

#include <iostream>     // cout, <<
#include <fstream>      // ifstream(), <<, >>
#include <cstdlib>      // exit(1);
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

void main(int argc, char *argv[]) {

  ///////////////////////////////////////////////////////////////
  title("Demonstration of Reading AND Writing to a Common File",'=');
  ///////////////////////////////////////////////////////////////

  if(argc < 2) {
    cout << "please enter file name on command line\n";
    exit(1);
  }

//

  ///////////////////////////////////////////////////////////////
  // file open modes:        in       out       app       ate  //
  //                             nocreate noreplace     trunc  //
  ///////////////////////////////////////////////////////////////

  // save input file contents in a temporary file 
  // for reading and writing

  ifstream masterin(argv[argc-1]);
  ofstream tempout("tmp.tmp");
  tempout << masterin.rdbuf();
  masterin.close();
  tempout.close();

  // open temporary for input AND output processing
  ifstream in("tmp.tmp", ios::in|ios::out);
  if(!in.good()) {
    cout << "can't open file tmp.tmp" << endl;
    exit(1);
  }

  // use input stream buffer for output stream too
  ostream out(in.rdbuf());

  // now, try reading and writing
  
  title("this is a test file for reading and writing");
  /////////////////////////////////////////////////////

  cout << in.rdbuf();
  out << "---\nthis text is added to the end\n";

  // how many bytes in file?
  streampos sp = out.tellp();
  out.seekp(-sp, ios::end);            // back up from end
  out << "this text overwrites beginning of file\n";
  cout << endl;

  // write it out to see what happened
 
  title("modified file:");
  ////////////////////////

  in.seekg(ios::beg);                  // go to beginning
  cout << in.rdbuf() << endl;
}
