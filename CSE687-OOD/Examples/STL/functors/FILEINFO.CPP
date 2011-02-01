///////////////////////////////////////////////////////////////
//                                                           //
//  fileInfo.cpp - manage file information extracted         //
//  ver 1.5        from win32 API                            //
//                                                           //
//  Language:      Visual C++, ver 5.0                       //
//  Platform:      Micron Dual Pentium 200, Windows NT 4.0   //
//  Application:   CSE687 Project #1, S98                    //
//  Author:        Jim Fawcett, CST 2-187, (315) 443-3948    //
//                 fawcett@ecs.syr.edu                       //
//                                                           //
///////////////////////////////////////////////////////////////

#pragma warning(disable : 4786)
#include <iostream>
#include <iomanip>
#include <set>
#include "fileInfo.h"

using namespace std;

//----< void constructor >-------------------------------------

fileInfo::fileInfo() {

  _origPath = getPath();
}

//----< constructor taking path >------------------------------

fileInfo::fileInfo(const string &path) {

  _origPath = getPath();
  setPath(path);
}

//

//----< copy constructor >-------------------------------------

fileInfo::fileInfo(const fileInfo &fi) {

  data.dwFileAttributes    = fi.data.dwFileAttributes;
  data.ftCreationTime      = fi.data.ftCreationTime;  
  data.ftLastAccessTime    = fi.data.ftLastAccessTime;
  data.ftLastWriteTime     = fi.data.ftLastWriteTime; 
  data.nFileSizeHigh       = fi.data.nFileSizeHigh;
  data.nFileSizeLow        = fi.data.nFileSizeLow; 
  data.dwReserved0         = fi.data.dwReserved0;
  data.dwReserved1         = fi.data.dwReserved1;
  int i;
  for(i=0; i<MAX_PATH; i++) {
    data.cFileName[i]      = fi.data.cFileName[i];
    if(fi.data.cFileName[i] == '\0')
      break;
  }
  for(i=0; i<14; i++)
    data.cAlternateFileName[i] = fi.data.cAlternateFileName[i];
  _origPath = getPath();
}

//----< destructor >-------------------------------------------

fileInfo::~fileInfo() {

  setPath(_origPath);
}

//----< assignment operator >----------------------------------

fileInfo& fileInfo::operator=(const fileInfo &fi) {

  if(this == &fi) return *this;
  data.dwFileAttributes    = fi.data.dwFileAttributes;
  data.ftCreationTime      = fi.data.ftCreationTime;  
  data.ftLastAccessTime    = fi.data.ftLastAccessTime;
  data.ftLastWriteTime     = fi.data.ftLastWriteTime; 
  data.nFileSizeHigh       = fi.data.nFileSizeHigh;
  data.nFileSizeLow        = fi.data.nFileSizeLow; 
  data.dwReserved0         = fi.data.dwReserved0;
  data.dwReserved1         = fi.data.dwReserved1;
  int i;
  for(i=0; i<MAX_PATH; i++)
    data.cFileName[i]      = fi.data.cFileName[i];
  for(i=0; i<14; i++)
    data.cAlternateFileName[i] = fi.data.cAlternateFileName[i];
  return *this;
}

//

//----< get file size >----------------------------------------

#pragma warning(disable:4293)

unsigned long int fileInfo::size() const {

  DWORDLONG myDWL = (data.nFileSizeHigh << 32);
  myDWL += (data.nFileSizeLow & 0xFFFFFFFF);
  return static_cast<unsigned long int>(myDWL);
}

//----< is my size smaller? >----------------------------------

bool fileInfo::smaller(const fileInfo &fi) const {
  
  DWORDLONG myDWL = (data.nFileSizeHigh << 32);
  myDWL += data.nFileSizeLow & 0xFFFFFFFF;
  DWORDLONG fiDWL = (fi.data.nFileSizeHigh << 32);
  fiDWL += fi.data.nFileSizeLow & 0xFFFFFFFF;
  return (myDWL < fiDWL);
}

//----< is my size larger? >-----------------------------------

bool fileInfo::larger(const fileInfo &fi) const {
  
  DWORDLONG myDWL = (data.nFileSizeHigh << 32);
  myDWL += data.nFileSizeLow & 0xFFFFFFFF;
  DWORDLONG fiDWL = (fi.data.nFileSizeHigh << 32);
  fiDWL += fi.data.nFileSizeLow & 0xFFFFFFFF;
  return (myDWL > fiDWL);
}

//----< private date and time extraction >---------------------

SYSTEMTIME fileInfo::DateAndTime() const {

 SYSTEMTIME st;
 FILETIME  lft;
 FileTimeToLocalFileTime(&data.ftLastWriteTime,&lft);
 FileTimeToSystemTime(&lft,&st);
 return st;
}

//

//----< get file date string >---------------------------------

string fileInfo::date() const {

  SYSTEMTIME st = DateAndTime();
  string date;
  date.resize(0);
  date += '0' + (st.wMonth / 10);
  date += '0' + (st.wMonth % 10);
  date += '/';
  date += '0' + (st.wDay / 10);
  date += '0' + (st.wDay % 10);
  date += '/';
  int tmp = st.wYear;
  date += '0' + (tmp/1000);
  tmp  %= 1000;
  date += '0' + (tmp / 100);
  tmp %= 100;
  date += '0' + (tmp / 10);
  tmp %= 10;
  date += '0' + (tmp);
  return date;
}

//----< get file time string >---------------------------------

string fileInfo::time() const {

  SYSTEMTIME st = DateAndTime();
  string time;
  string AMPM = "am";
  if(st.wHour > 12) {
    st.wHour -= 12;
    AMPM = "pm";
  }
  time.erase();
  time += '0' + (st.wHour   / 10);
  time += '0' + (st.wHour   % 10);
  time += ':';
  time += '0' + (st.wMinute / 10);
  time += '0' + (st.wMinute % 10);
//  time += ':';
//  time += '0' + (st.wSecond / 10);
//  time += '0' + (st.wSecond % 10);
  time += " ";
  time += AMPM;
  return time;
}

//

//----< make attributes string >-------------------------------

string fileInfo::attributes() const {

  string temp;
  if(isArchive()   ) temp += 'A';
  if(isCompressed()) temp += 'C';
  if(isDirectory() ) temp += 'D';
  if(isEncrypted() ) temp += 'E';
  if(isHidden()    ) temp += 'H';
  if(isOffLine()   ) temp += 'O';
  if(isReadOnly()  ) temp += 'R';
  if(isSystem()    ) temp += 'S';
  if(isTemporary() ) temp += 'T';
  return temp;
}

//----< pragma needed to disable performance warning >---------
//
//  for some reason casts don't inhibit warning as they should

#pragma warning(disable : 4800)

//----< is this file Archive? >--------------------------------

bool fileInfo::isArchive() const { 
  
  return (data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE);
}

//----< is this file Compressed? >-----------------------------

bool fileInfo::isCompressed() const { 
  
  return (data.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED); 
}

//----< is this file Directory? >------------------------------

bool fileInfo::isDirectory() const { 
  
  return (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY); 
}

//

//----< is this file Encrypted? >------------------------------

bool fileInfo::isEncrypted() const { 
  
  return (data.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED); 
}

//----< is this file Hidden? >---------------------------------

bool fileInfo::isHidden() const { 
  
  return (data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN); 
}

//----< is this file Normal? >---------------------------------

bool fileInfo::isNormal() const { 
  
  return (data.dwFileAttributes & FILE_ATTRIBUTE_NORMAL); 
}

//----< is this file OffLine? >--------------------------------

bool fileInfo::isOffLine() const { 
  
  return (data.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE); 
}

//----< is this file ReadOnly? >-------------------------------

bool fileInfo::isReadOnly() const { 
  
  return (data.dwFileAttributes & FILE_ATTRIBUTE_READONLY); 
}

//----< is this file System? >---------------------------------

bool fileInfo::isSystem() const { 
  
  return (data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM); 
}

//----< is this file Temporary? >------------------------------

bool fileInfo::isTemporary() const { 
  
  return (data.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY); 
}

//

//----< display line of file data >----------------------------

void fileInfo::showData(ostream &out, char ch) const {

  out << "  " << setw(15) << name();
  out << setw(10) << size();
  out << "  " << date();
  out << "  " << time();
  out << "  " << attributes();
  out << ch;
}

//----< get current directory >--------------------------------

string fileInfo::getPath() {

  char buffer[256];
  GetCurrentDirectory(256,buffer);
  return buffer;
}

//----< set current directory >--------------------------------

void fileInfo::setPath(const string &s) {

  SetCurrentDirectory(s.c_str());
}

//----< find first file >--------------------------------------

bool fileInfo::firstFile(const string &filePattern) {

  _handle = FindFirstFile(filePattern.c_str(),&data);
  return (_handle != INVALID_HANDLE_VALUE);
}

//----< find next file >---------------------------------------

bool fileInfo::nextFile() {

  if(_handle == INVALID_HANDLE_VALUE)
    return false;
  return (FindNextFile(_handle,&data) == TRUE);
}

//----< close search for current file >------------------------

void fileInfo::closeFile() {  FindClose(_handle); }

//

//----< test stub >--------------------------------------------

#ifdef TEST_FILEINFO

//----< function object which detects date order >-------------

class earlier {
  
public:
  bool operator()(const fileInfo &fi1, const fileInfo &fi2) {
    return fi1.earlier(fi2);
  }
};

//----< function object which detects size order >-------------

class smaller {
  
public:
  bool operator()(const fileInfo &fi1, const fileInfo &fi2) {
    return fi1.smaller(fi2);
  }
};

//----< test entry point >-------------------------------------

void main(int argc, char *argv[]) {

  cout << "\n  Testing Fileinfo objects "
       << "\n ==========================\n";

  typedef set< fileInfo, less<fileInfo> > setNames;   // names are unique
  typedef multiset< fileInfo, earlier > setDates;     // dates may not be
  typedef multiset< fileInfo, smaller > setSizes;     // sizes may not be

  fileInfo f;
  if(argc > 1)
    f.setPath(argv[1]);
  cout << "  path = " << f.getPath() << endl;

//

  cout << "\n  Files in FindNextFile Order\n";
  setNames sn;
  setDates sd;
  setSizes ss;

  if(!f.firstFile("*.*"))
    return;
  sn.insert(f);
  sd.insert(f);
  ss.insert(f);
  f.showData(cout);
  while(f.nextFile()) {
    sn.insert(f);
    sd.insert(f);
    ss.insert(f);
    f.showData(cout);
  }

  cout << "\n  Files ordered alphabetically:\n";
  setNames::iterator fnIt;
  for(fnIt = sn.begin(); fnIt != sn.end(); fnIt++) {
    fnIt->showData(cout);
  }
  cout << "\n  Files ordered by date:\n";
  setDates::iterator fdIt;
  for(fdIt = sd.begin(); fdIt != sd.end(); fdIt++) {
    fdIt->showData(cout);
  }
  cout << "\n  Files ordered by size:\n";
  setSizes::iterator fsIt;
  for(fsIt = ss.begin(); fsIt != ss.end(); fsIt++) {
    fsIt->showData(cout);
  }
  cout << "\n\n";
}

#endif
