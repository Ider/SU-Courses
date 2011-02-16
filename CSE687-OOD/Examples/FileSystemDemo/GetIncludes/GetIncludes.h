#ifndef GETINCLUDES_H
#define GETINCLUDES_H
/////////////////////////////////////////////////////////////////////////////
// GetIncludes.h - Process C++ files include statements                    //
// ver 1.0                                                                 //
// Language:    Visual C++, Visual Studio 2008                             //
// Platform:    Dell Precision T7400, Quad core Xeons, Vista Ultimate, SP1 //
// Application: CSE687 - OOD, demonstration, Spring 2009                   //
// Author:      Jim Fawcett, CST 4-187, Syracuse University                //
//              (315) 443-3948, jfawcett@twcny.rr.com                      //
/////////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * This module provides the class Includes that provides support for
 * C++ include statements.  It does this using fairly simple string
 * operations, with a lot of help from the FileSystem module.
 *
 * Public Interface:
 * =================
 * FileHandler fh;
 * Includes::vector hdrs = fh.getFiles(path, *.h);
 * Includes::vector imps = fh.getFiles(path, *.cpp);
 * Includes::vector merged = Includes::mergeFiles(hdrs, imps);
 * Includes::showFull(merged);
 * Includes::show(merged);
 * File f(fullyQualifiedFileName,File::in);
 * while(f.isGood())
 * {
 *   std::string line = f.getLine();
 *   line = Includes::getIncludedFileSpec(line,Include::local);
 *   if(line.size() > 0)
 *     // do something with included fileSpec
 * }
 *
 * Required Files:
 * ===============
 * GetIncludes.h, GetIncludes.cpp, FileSystem.h, FileSystem.cpp
 *
 * Build Command:
 * ==============
 * cl /EHa /DTEST_FILESYSTEM GetIncludes.cpp FileSystem.cpp
 *
 * Maintenance History:
 * ====================
 * ver 1.0 : 21 Feb 09
 * - first release
 */

class Includes
{
public:
  typedef std::vector<std::string> vector;
  enum includeType { system, local };
  static std::string getIncludedFileSpec(const std::string& line, includeType type);
  static vector mergeFiles(const vector& f, const vector& g);
  static void showFull(const vector& files, const std::string& msg="");
  static void show(const vector& files, const std::string& msg="");
};

#endif
