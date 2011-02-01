#ifndef FILEINFO_H
#define FILEINFO_H
///////////////////////////////////////////////////////////////
//                                                           //
//  fileInfo.h  -  manage file information extracted         //
//  ver 1.5        from win32 API                            //
//                                                           //
//  Language:      Visual C++, ver 5.0                       //
//  Platform:      Micron Dual Pentium 200, Windows NT 4.0   //
//  Application:   CSE687 Project #1, S98                    //
//  Author:        Jim Fawcett, CST 2-187, (315) 443-3948    //
//                 fawcett@neptune.syr.edu                   //
//                                                           //
///////////////////////////////////////////////////////////////
/*

    class fileInfo Operations:
    --------------------------
    The fileInfo class acquires file information from win32 API
    functions and returns parts of the information on demand.
    Specifically a fileInfo object extracts file name, size,
    and time and date of last modification for each file matching
    a pattern in the current directory.

    A fileInfo object saves the current directory path when created
    and its destructor restores that original path before the object
    is destroyed.

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

      string path = fi.getPath();      get name of current dir
      fi.setPath(const string &path);  set current dir to path

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
//  Building with Visual C++ , ver 5.0, from command line:   //
//    cl -GX -DTEST_FILEINFO fileInfo.cpp                    //
//                                                           //
///////////////////////////////////////////////////////////////
/*

    Maintenance History
    ===================
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

class fileInfo {

  friend class navig;

public:
  fileInfo();
  fileInfo(const fileInfo &fi);
  fileInfo(const std::string &path);
  ~fileInfo();

  bool firstFile(const std::string &filePattern);
  bool nextFile();
  void closeFile();
  std::string       name() const;
  unsigned long int size() const;
  std::string       date() const;
  std::string       time() const;
  std::string       attributes() const;
  bool isArchive()     const;
  bool isCompressed() const;
  bool isDirectory()  const;
  bool isEncrypted()  const;
  bool isHidden()     const;
  bool isNormal()     const;
  bool isOffLine()    const;
  bool isReadOnly()   const;
  bool isSystem()     const;
  bool isTemporary()  const;

  fileInfo& operator=(const fileInfo &fi);
  bool operator< (const fileInfo &fi) const;
  bool operator==(const fileInfo &fi) const;
  bool earlier   (const fileInfo &fi) const;
  bool later     (const fileInfo &fi) const;
  bool smaller   (const fileInfo &fi) const;
  bool larger    (const fileInfo &fi) const;

  void showData  (std::ostream &out,char ch='\n') const;
  std::string getPath(void);
  void setPath(const std::string &s);

private:
  WIN32_FIND_DATA data;
  HANDLE _handle;
  std::string _origPath;
  SYSTEMTIME DateAndTime() const;
};


//

//----< return file name >-------------------------------------

inline std::string fileInfo::name() const { return data.cFileName; }

//----< less than operator >-----------------------------------

inline bool fileInfo::operator<(const fileInfo &fd) const {

  return (strcmp(data.cFileName,fd.data.cFileName) == -1);
}

//----< comparison operator >----------------------------------

inline bool fileInfo::operator==(const fileInfo &fi) const { 
  
  return (strcmp(data.cFileName,fi.data.cFileName) == 0);
}

//----< comparison of file time and date >---------------------

inline bool fileInfo::earlier(const fileInfo &fi) const {

  return (
    CompareFileTime(&data.ftLastWriteTime,&fi.data.ftLastWriteTime) == -1
  );
}

//----< comparison of file time and date >---------------------

inline bool fileInfo::later(const fileInfo &fi) const {

  return (
    CompareFileTime(&data.ftLastWriteTime,&fi.data.ftLastWriteTime) == 1
  );
}

#endif
