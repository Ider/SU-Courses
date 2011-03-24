///////////////////////////////////////////////////////////////
// fileio.cpp - demonstrate fstreams                         //
//                                                           //
// Jim Fawcett, 24 Mar 96, modified 04 Mar 02                //
///////////////////////////////////////////////////////////////

#include <iostream>     // cout, <<
#include <fstream>      // ifstream(), <<, >>
#include <cstdlib>      // exit(1);
#include <sstream>
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

  /////////////////////////////////////////////////
  title("Demonstrating Basic File Operations",'=');
  /////////////////////////////////////////////////

  if(argc < 2) {
    cout << "\nplease enter name of text file on command line\n\n";
    exit(1);
  }
  const int bufSize = 80;
  char buffer[bufSize];

//

  // create a scope with { } and define an input stream inside
  // then read line-by-line and send to standard output
  {
    ifstream in(argv[argc-1]);
    if(!in.good()) {
      cout << "can't open file " << argv[argc-1] << endl;
      exit(1);
    }
    else {
      ostringstream temp;
      temp << "processing file " << argv[argc-1]
           << " using istream::getline()";

      title(temp.str().c_str());
      //////////////////////////
    }

    while(in.good()) {
      in.getline(buffer,bufSize);
      cout << buffer << endl;
    }
  }  // in goes out of scope and is destroyed

  // define stream again at global level, get pointer to
  // its filebuf and stream input directly to output

  ostringstream temp;
  temp << "processing file " << argv[argc-1]
       << " using filebuf::rdbuf()";
  title(temp.str().c_str());
  //////////////////////////
  
  ifstream in(argv[argc-1]);
  filebuf *bptr = in.rdbuf();    // get pointer to stream
  cout << bptr << endl;          // stream input to output
  in.close();                    // still in scope so close it

//

  // open stream again, seek to end to find size, and
  // backup half way, then send last half to stdout

  in.open(argv[argc-1]);         // open it again
  in.seekg(0, ios::end);         // go to end of file
  streampos sp = in.tellg();     // size = number of bytes from beg
  in.seekg(-sp/2, ios::end);     // go to middle
  in.getline(buffer,bufSize);    // go to next newline

  ostringstream temp2;
  temp2 << "processing last half of this " << sp << " byte file";
  title(temp2.str().c_str());
  ///////////////////////////

  cout << in.rdbuf() << endl;    // output from that point to end

  title("stream state goes bad when attempting to read past end of file");
  ////////////////////////////////////////////////////////////////////////

  char ch;
  in >> ch;
  if(!in.good())
    cout << "  attempting to read past EOF makes stream state"
         << " not good\n";

  title("can't read any more until we clear stream to good state");
  /////////////////////////////////////////////////////////////////

  in.clear();
  if(in.good())
    cout << "  stream state good after clear()\n";
  in.seekg(-1,ios::end);         // back up to good char
  in >> ch;
  if(in.good())
    cout << "  after backing up and reading " << ch
         << " stream state still good\n";
  in >> ch;
  if(!in.good())
    cout << "  after reading EOF stream state not good again\n";
  cout << endl;
}
