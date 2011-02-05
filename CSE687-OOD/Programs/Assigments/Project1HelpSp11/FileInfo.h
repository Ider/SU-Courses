#ifndef FILEINFO_H
#define FILEINFO_H
///////////////////////////////////////////////////////////////////////
//  fileInfo.h  -  manage file information extracted from Win32 API  //
//  ver 2.7                                                          //
//  Language:      Visual C++, ver 7.1                               //
//  Platform:      Dell Dimension 9150, Windows XP Pro, SP2          //
//  Application:   CSE687 Project #1, Spring 2006                    //
//  Author:        Jim Fawcett, Syracuse University CST 2-187,       //
//                 (315) 443-3948, jfawcett@twcny.rr.com             //
///////////////////////////////////////////////////////////////////////
/*
    class fileInfo Operations:
    --------------------------
    FileInfo provides a convenient way of finding all the files in
    a specific directory, as well as their associated attributes.

    The fileInfo class acquires file information from win32 API
    functions and returns parts of the information on demand.
    Specifically a fileInfo object extracts file name, size,
    and time and date of last modification for each file matching
    a pattern in the current directory.

    A fileInfo object saves the current directory path when created
    and its destructor restores that original path before the object
    is destroyed.  One function, setPath(const string&), will throw
    an exception if the path is invalid.  Handling of this exception
    is deferred to application code as fileInfo doesn't know what to
    do about that condition.  The test stub shows how an application
    can do that.

    Public Interface:
    -----------------
      fileInfo fi;                     void construct
      fileInfo fi(d:\test);            constructor setting path
      fileInfo fi2 = fi1;              copy constructor
      bool b = fi.firstFile("*.cpp");  find first file matching in
                                       current dir, true if exists
      bool b = fi.nextFile();          find next file matching
                                       pattern in current dir
      fi.closeFile();                  close file search
      string n = fi.name();            file name
      string d = fi.date();            file date last modified
      string t = fi.time();            file time last modified
      unsigned long int s = fi.size(); file size
      if(fi1 <  fi2) {...}             test file name order
      if(fi1 == fi2) {...}             test file name equality
      if(fi1.later(fi2)) {...}         test file time
      if(fi1.earlier(fi2)) {...}       test file time
      if(fi1.smaller(fi2)) {...}       test file size
      if(fi1.larger (fi2)) {...}       test file size
      fi.showData(cout);               display file data
      fi.showData(cout,'');            display with no return

      FILETIME ft = fi.getFILETIME();  return this file's FILETIME structure
      retVal = fi.compareFileTime(ft); return 1, 0, -1 if ft is earlier
                                         same, or later, respectively
      string path = fi.getPath();      get name of current dir
      fi.setPath(const string &path);  set current dir to path
      path = fi.getPath();             return current path
      path = fi.lastSetPath();         returns last path set

    See test stub for example of how to use fileInfo object with STL
    containers to get sets of files, sorted by name, date, or size.
*/
//

///////////////////////////////////////////////////////////////
//                      maintenance page                     //
///////////////////////////////////////////////////////////////
//  Build Process                                            //
//                                                           //
//  Files Required:                                          //
//    fileInfo.h, fileInfo.cpp                               //
//                                                           //
//  Building with Visual C++ , 8.0, from command line:       //
//    cl -EHsc -DTEST_FILEINFO fileInfo.cpp                  //
//                                                           //
///////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 2.7 : 19 Jan 05
    - added case insensitive file name comparisons
    - modified display in showData
    - eliminated some warnings with an appropriate static_cast
    - fixed constructor and operator= initialization bugs
    ver 2.6 : 22 Jan 05
    - added manual page information about exception handling
    ver 2.5 : 17 Jan 05
    - added display options and made cosmetic changes
    ver 2.4 : 03 May 04
    - added lastSetPath() to retrieve the last path searched.
    ver 2.3 : 01 May 04
    - the last fix broke recursion, reported by Kurt Denhoff, now
      fixed and uploaded to class code folder in getfiles and 
      fileInfo subfolders
    ver 2.2 : 27 Apr 04
    - added support for extracting and comparing FILETIME structures
    - setPath(const std::string&) now throws an invalid_argument
      exception if the path does not exist
    ver 2.1 : 23 Jan 04
    - cosmetic changes - eliminated a couple of comments and an
      unused line of code.
    ver 2.0 : 04 Apr 01
    - changed design so that directories are never set.  Now uses
      a specified path for file finding without changing the
      current directory
    ver 1.5 : 12 Jun 00
      - added extraction of attributes
    ver 1.4 : 29 Jan 00
      - added tests for earlier and smaller member functions in 
        test stub
    ver 1.3 : 14 Jul 99
      - more cosmetic modification to header file
    ver 1.2 : 11 Jul 99
      - added member function fileClose()
      - cosmetic modifications to both header and implem. files.
    ver 1.1 : 05 Jul 99
      - modified member function args, removing WIN32_FIND_DATA
        structures from all member function parameter lists
      - added firstFile(...) and nextFile() functions
      - save and restore original path
    ver 1.0 : 07 Feb 98
      - first release

    Planned Modifications:
    ======================
    - none
*/
//

///////////////////////////////////////////////////////////////
//                         Declarations                      //
///////////////////////////////////////////////////////////////

#include <windows.h>
#include <string>

class fileInfo 
{
public:

  // object management
  fileInfo();
  fileInfo(const fileInfo &fi);
  fileInfo(const std::string &path);
  ~fileInfo();
  fileInfo& operator=(const fileInfo &fi);

  // search
  bool firstFile(const std::string &filePattern);
  bool nextFile();
  void closeFile();

  // file information
  std::string       name() const;
  unsigned long int size() const;
  std::string       date() const;
  std::string       time() const;
  FILETIME          getFILETIME();
  int               compareFileTime(FILETIME& ft);
  std::string       attributes() const;
  bool isArchive()    const;
  bool isCompressed() const;
  bool isDirectory()  const;
  bool isEncrypted()  const;
  bool isHidden()     const;
  bool isNormal()     const;
  bool isOffLine()    const;
  bool isReadOnly()   const;
  bool isSystem()     const;
  bool isTemporary()  const;

  // name comparisons
  bool operator< (const fileInfo &fi) const;
  bool operator==(const fileInfo &fi) const;

  // time comparisons
  bool earlier   (const fileInfo &fi) const;
  bool later     (const fileInfo &fi) const;

  // size comparisons
  bool smaller   (const fileInfo &fi) const;
  bool larger    (const fileInfo &fi) const;

  // directory management
  std::string lastSetPath();
  static std::string getPath();
  void setPath(const std::string& s);

//

  // quick display
  void showData(std::ostream &out,char ch='\n',int width=20) const;
  void showSize(bool show_size=true);
  void showSeconds(bool show_seconds=false);
  void showTime(bool show_time=true);
  void showDate(bool show_date=true);
  void showAttributes(bool show_attrib=true);

private:
  WIN32_FIND_DATA data;
  HANDLE _handle;
  SYSTEMTIME DateAndTime() const;
  std::string _OrigPath;
  std::string _CurrPath;
  bool showSize_;
  bool showSeconds_;
  bool showTime_;
  bool showDate_;
  bool showAttrib_;
};

//----< return last path searched >----------------------------

inline std::string fileInfo::lastSetPath() { return _CurrPath; }

//----< return file name >-------------------------------------

inline std::string fileInfo::name() const { return data.cFileName; }

//----< less than operator >-----------------------------------

inline bool fileInfo::operator<(const fileInfo &fd) const 
{
  return (strcmp(data.cFileName,fd.data.cFileName) == -1);
}

//----< comparison operator >----------------------------------

inline bool fileInfo::operator==(const fileInfo &fi) const 
{  
  return (strcmp(data.cFileName,fi.data.cFileName) == 0);
}

//----< comparison of file time and date >---------------------

inline bool fileInfo::earlier(const fileInfo &fi) const 
{
  return (
    CompareFileTime(&data.ftLastWriteTime,&fi.data.ftLastWriteTime) == -1
  );
}

//----< comparison of file time and date >---------------------

inline bool fileInfo::later(const fileInfo &fi) const 
{
  return (
    CompareFileTime(&data.ftLastWriteTime,&fi.data.ftLastWriteTime) == 1
  );
}
//
//----< display size? >----------------------------------------

inline void fileInfo::showSize(bool show_size)
{
  showSize_ = show_size;
}
//----< display time? >----------------------------------------

inline void fileInfo::showTime(bool show_time)
{
  showTime_ = show_time;
}
//----< display seconds in file time? >------------------------

inline void fileInfo::showSeconds(bool show_seconds)
{
  showSeconds_ = show_seconds;
}
//----< display date? >----------------------------------------

inline void fileInfo::showDate(bool show_date)
{
  showDate_ = show_date;
}
//----< display attributes? >----------------------------------

inline void fileInfo::showAttributes(bool show_attrib)
{
  showAttrib_ = show_attrib;
}

#endif
