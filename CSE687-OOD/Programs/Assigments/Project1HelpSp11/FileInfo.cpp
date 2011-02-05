///////////////////////////////////////////////////////////////////////
//  fileInfo.cpp - manage file information extracted from Win32 API  //
//  ver 2.7                                                          //
//  Language:      Visual C++, ver 7.1                               //
//  Platform:      Dell Dimension 8300, Windows XP Pro, SP2          //
//  Application:   CSE687 Project #1, Spring 2005                    //
//  Author:        Jim Fawcett, Syracuse University CST 2-187,       //
//                 (315) 443-3948, jfawcett@twcny.rr.com             //
///////////////////////////////////////////////////////////////////////

#pragma warning(disable : 4786)
#include <iostream>
#include <iomanip>
#include <set>
#include "fileInfo.h"

//----< void constructor >-------------------------------------

fileInfo::fileInfo()
        : showSeconds_(false), showTime_(true), showDate_(true),
          showSize_(true), showAttrib_(true)
{ 
  _CurrPath = _OrigPath = getPath();
}
//----< constructor taking path >------------------------------

fileInfo::fileInfo(const std::string &path) 
        : showSeconds_(false), showTime_(true), showDate_(true),
          showSize_(true), showAttrib_(true)
{
  _OrigPath = getPath();
  setPath(path);
}
//
//----< copy constructor >-------------------------------------

fileInfo::fileInfo(const fileInfo &fi) 
: showSeconds_(fi.showSeconds_), showTime_(fi.showTime_),
showDate_(fi.showDate_), showSize_(fi.showSize_), showAttrib_(fi.showAttrib_)
{
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
  {
    data.cFileName[i]      = fi.data.cFileName[i];
    if(fi.data.cFileName[i] == '\0')
      break;
  }
  for(i=0; i<14; i++)
    data.cAlternateFileName[i] = fi.data.cAlternateFileName[i];

  _OrigPath = fi._OrigPath;
  _CurrPath = fi._CurrPath;
  showSeconds_ = fi.showSeconds_;
}
//----< destructor >-------------------------------------------

fileInfo::~fileInfo() { setPath(_OrigPath); }

//----< assignment operator >----------------------------------

fileInfo& fileInfo::operator=(const fileInfo &fi) 
{
  if(this == &fi) return *this;
  data.dwFileAttributes    = fi.data.dwFileAttributes;
  data.ftCreationTime      = fi.data.ftCreationTime;  
  data.ftLastAccessTime    = fi.data.ftLastAccessTime;
  data.ftLastWriteTime     = fi.data.ftLastWriteTime; 
  data.nFileSizeHigh       = fi.data.nFileSizeHigh;
  data.nFileSizeLow        = fi.data.nFileSizeLow; 
  data.dwReserved0         = fi.data.dwReserved0;
  data.dwReserved1         = fi.data.dwReserved1;
  showSize_ = fi.showSize_;
  showSeconds_ = fi.showSeconds_;
  showTime_ = fi.showTime_;
  showDate_ = fi.showDate_;
  showAttrib_ = fi.showAttrib_;
  int i;
  for(i=0; i<MAX_PATH; i++)
    data.cFileName[i]      = fi.data.cFileName[i];
  for(i=0; i<14; i++)
    data.cAlternateFileName[i] = fi.data.cAlternateFileName[i];
  _OrigPath = fi._OrigPath;
  _CurrPath = fi._CurrPath;

  return *this;
}
//
//----< get file size >----------------------------------------

unsigned long int fileInfo::size() const 
{
  DWORDLONG myDWL = (static_cast<DWORDLONG>(data.nFileSizeHigh) << 32);
  myDWL += (data.nFileSizeLow & 0xFFFFFFFF);
  return static_cast<unsigned long int>(myDWL);
}
//----< is my size smaller? >----------------------------------

bool fileInfo::smaller(const fileInfo &fi) const 
{  
  DWORDLONG myDWL = (static_cast<DWORDLONG>(data.nFileSizeHigh) << 32);
  myDWL += data.nFileSizeLow & 0xFFFFFFFF;
  DWORDLONG fiDWL = (static_cast<DWORDLONG>(fi.data.nFileSizeHigh) << 32);
  fiDWL += fi.data.nFileSizeLow & 0xFFFFFFFF;
  return (myDWL < fiDWL);
}
//----< is my size larger? >-----------------------------------

bool fileInfo::larger(const fileInfo &fi) const 
{  
  DWORDLONG myDWL = (static_cast<DWORDLONG>(data.nFileSizeHigh) << 32);
  myDWL += data.nFileSizeLow & 0xFFFFFFFF;
  DWORDLONG fiDWL = (static_cast<DWORDLONG>(fi.data.nFileSizeHigh) << 32);
  fiDWL += fi.data.nFileSizeLow & 0xFFFFFFFF;
  return (myDWL > fiDWL);
}
//----< return FILETIME >--------------------------------------
//
//  typedef struct _FILETIME
//  { DWORD dwLowDateTime;  DWORD dwHighDateTime; } FILETIME;
//
FILETIME fileInfo::getFILETIME()
{
  FILETIME lft;
  FileTimeToLocalFileTime(&data.ftLastWriteTime,&lft);
  return lft;
}
//----< compare file times >-----------------------------------
//
//  returns 1 if my FILETIME is later than ft
//          0 if my FILETIME equals ft
//         -1 if my FILETIME is earlier than ft
//
int fileInfo::compareFileTime(FILETIME& ft)
{
  FILETIME myft = getFILETIME();
  return (int)::CompareFileTime(&myft,&ft);
}
//
//----< private date and time extraction >---------------------

SYSTEMTIME fileInfo::DateAndTime() const 
{
 SYSTEMTIME st;
 FILETIME  lft;
 FileTimeToLocalFileTime(&data.ftLastWriteTime,&lft);
 FileTimeToSystemTime(&lft,&st);
 return st;
}
//----< get file date string >---------------------------------

std::string fileInfo::date() const 
{
  SYSTEMTIME st = DateAndTime();
  std::string date;
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

std::string fileInfo::time() const 
{
  SYSTEMTIME st = DateAndTime();
  std::string time;
  std::string AMPM = "am";
  if(st.wHour > 12) 
  {
    st.wHour -= 12;
    AMPM = "pm";
  }
  time.erase();
  time += '0' + (st.wHour   / 10);
  time += '0' + (st.wHour   % 10);
  time += ':';
  time += '0' + (st.wMinute / 10);
  time += '0' + (st.wMinute % 10);
  if(showSeconds_)
  {
    time += ':';
    time += '0' + (st.wSecond / 10);
    time += '0' + (st.wSecond % 10);
  }
  time += " ";
  time += AMPM;
  return time;
}
//
//----< make attributes string >-------------------------------

std::string fileInfo::attributes() const 
{
  std::string temp;
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

bool fileInfo::isArchive() const 
{ 
  return (data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE);
}
//----< is this file Compressed? >-----------------------------

bool fileInfo::isCompressed() const 
{   
  return (data.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED); 
}
//----< is this file Directory? >------------------------------

bool fileInfo::isDirectory() const 
{   
  return (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY); 
}
//
//----< is this file Encrypted? >------------------------------

bool fileInfo::isEncrypted() const 
{   
  return (data.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED); 
}
//----< is this file Hidden? >---------------------------------

bool fileInfo::isHidden() const 
{   
  return (data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN); 
}
//----< is this file Normal? >---------------------------------

bool fileInfo::isNormal() const 
{   
  return (data.dwFileAttributes & FILE_ATTRIBUTE_NORMAL); 
}
//----< is this file OffLine? >--------------------------------

bool fileInfo::isOffLine() const 
{   
  return (data.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE); 
}
//----< is this file ReadOnly? >-------------------------------

bool fileInfo::isReadOnly() const 
{   
  return (data.dwFileAttributes & FILE_ATTRIBUTE_READONLY); 
}
//----< is this file System? >---------------------------------

bool fileInfo::isSystem() const 
{   
  return (data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM); 
}
//----< is this file Temporary? >------------------------------

bool fileInfo::isTemporary() const 
{   
  return (data.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY); 
}
//
//----< display line of file data >----------------------------

void fileInfo::showData(std::ostream &out, char ch, int width) const 
{
  long save = out.flags();
  out.setf(std::ios::right, std::ios::adjustfield);
  if(showSize_)
    out << std::setw(10) << size();
  if(showDate_)
    out << "  " << date();
  if(showTime_ && showDate_)
    out << "  " << time();
  if(showAttrib_)
    out << "  " << attributes();
  out.setf(std::ios::left, std::ios::adjustfield);
  out << "  " << std::setw(width) << name();
  out << ch;
  out.flush();
  out.flags(save);
}
//----< get current searchPath >-------------------------------
//
//  fill with current directory path if empty
//
std::string fileInfo::getPath() 
{
  char buffer[256];
  ::GetCurrentDirectory(256,buffer);
  return std::string(buffer);
}
//----< set current directory >--------------------------------

void fileInfo::setPath(const std::string& s) 
{
  if(::SetCurrentDirectory(s.c_str()) == 0)
  {
    std::string temp = s + " - path not found";
    throw std::invalid_argument(temp.c_str());
  }
  _CurrPath = s;
}
//
//----< find first file >--------------------------------------

bool fileInfo::firstFile(const std::string &filePattern) 
{
  closeFile();    // close any previous search
  std::string path = getPath();
  if(path[path.size()-1] != '\\')
    path += '\\';
  path += filePattern;
  _handle = ::FindFirstFile(path.c_str(),&data);
  return (_handle != INVALID_HANDLE_VALUE);
}
//----< find next file >---------------------------------------

bool fileInfo::nextFile() 
{
  if(_handle == INVALID_HANDLE_VALUE)
    return false;
  return (::FindNextFile(_handle,&data) == TRUE);
}
//----< close search for current file >------------------------

void fileInfo::closeFile() {  FindClose(_handle); }

//----< function object which detects case insensitive order >-------

class lessNoCase
{
public:
  bool operator()(const fileInfo &fi1, const fileInfo &fi2) {
    std::string name1 = fi1.name(), name2 = fi2.name();
    size_t leastSize = min(name1.size(), name2.size());
    for(size_t i=0; i<leastSize; ++i)
      if(tolower(name1[i]) > tolower(name2[i]))
        return false;
    return name1.size() < name2.size();
  }
};
//----< function object which detects date order >-------------

class earlier 
{
public:
  bool operator()(const fileInfo &fi1, const fileInfo &fi2) {
    return fi1.earlier(fi2);
  }
};
//----< function object which detects size order >-------------

class smaller 
{  
public:
  bool operator()(const fileInfo &fi1, const fileInfo &fi2) {
    return fi1.smaller(fi2);
  }
};
//
//----< test stub >--------------------------------------------

#ifdef TEST_FILEINFO

//----< test entry point >-------------------------------------

void main(int argc, char *argv[]) 
{
  std::cout << "\n  Testing Fileinfo objects "
            << "\n ==========================\n";

  // file names are unique, so use set

  typedef std::set< fileInfo, std::less<fileInfo>  > setNames;
  
  // lowercase file names, file dates, and file sizes
  // may not be unique, so use multiset

  typedef std::multiset< fileInfo, lessNoCase > setLCNames;
  typedef std::multiset< fileInfo, earlier > setDates;
  typedef std::multiset< fileInfo, smaller > setSizes;

  fileInfo f;
  f.showSeconds(true);
  try
  {
    if(argc > 1)
      f.setPath(argv[1]);
  }
  catch(std::exception& e) 
  { 
    std::cout << "\n\n  " << e.what() << "\n\n";
    f.setPath("..");
  }
  std::cout << "\n  path = " << f.getPath() << std::endl;

  std::cout << "\n  Files in FindNextFile Order\n";
  setNames sn;
  setLCNames sl;
  setDates sd;
  setSizes ss;

  if(!f.firstFile("*.*"))
    return;
  sn.insert(f);
  sl.insert(f);
  sd.insert(f);
  ss.insert(f);
  f.showData(std::cout);
  while(f.nextFile()) {
    sn.insert(f);
    sl.insert(f);
    sd.insert(f);
    ss.insert(f);
    f.showData(std::cout);
  }
  f.closeFile();
//

  std::cout << "\n  Files ordered alphabetically:\n";
  setNames::iterator fnIt;
  for(fnIt = sn.begin(); fnIt != sn.end(); fnIt++) {
    fnIt->showData(std::cout);
  }
  std::cout << "\n  Files with case insensitive alphabetic order:\n";
  setLCNames::iterator flIt;
  for(flIt = sl.begin(); flIt != sl.end(); flIt++) {
    flIt->showData(std::cout);
  }
  std::cout << "\n  Files ordered by date:\n";
  setDates::iterator fdIt;
  for(fdIt = sd.begin(); fdIt != sd.end(); fdIt++) {
    fdIt->showData(std::cout);
  }
  std::cout << "\n  Files ordered by size:\n";
  setSizes::iterator fsIt;
  for(fsIt = ss.begin(); fsIt != ss.end(); fsIt++) {
    fsIt->showData(std::cout);
  }
  std::cout << "\n\n";

  std::cout << "\n  Comparing file times:\n";
  setDates::iterator first = sd.begin();
  setDates::iterator second = first;
  ++second;
  std::cout << "\n  " << (*first).name() << " has date: "
            << (*first).date() << ", " << (*first).time();
  std::cout << "\n  " << (*second).name() << " has date: "
            << (*second).date() << ", " << (*second).time();
  int retVal = (*first).compareFileTime((*second).getFILETIME());
  if(retVal > 0)
    std::cout << "\n  " << (*first).name() 
              << " is later than " << (*second).name();
  if(retVal == 0)
    std::cout << "\n  " << (*first).name() 
              << " is same time as " << (*second).name();
  if(retVal < 0)
    std::cout << "\n  " << (*first).name() 
              << " is earlier than " << (*second).name();

  retVal = (*second).compareFileTime((*first).getFILETIME());
  if(retVal > 0)
    std::cout << "\n  " << (*second).name() 
              << " is later than " << (*first).name();
  if(retVal == 0)
    std::cout << "\n  " << (*second).name() 
              << " is same time as " << (*first).name();
  if(retVal < 0)
    std::cout << "\n  " << (*second).name() 
              << " is earlier than " << (*first).name();
//
  retVal = (*first).compareFileTime((*first).getFILETIME());
  if(retVal > 0)
    std::cout << "\n  " << (*first).name() 
              << " is later than " << (*first).name();
  if(retVal == 0)
    std::cout << "\n  " << (*first).name() 
              << " is same time as " << (*first).name();
  if(retVal < 0)
    std::cout << "\n  " << (*first).name() 
              << " is earlier than " << (*first).name();


  std::cout << "\n\n  Last search path = " << f.lastSetPath();
  std::cout << "\n\n";
}
#endif
