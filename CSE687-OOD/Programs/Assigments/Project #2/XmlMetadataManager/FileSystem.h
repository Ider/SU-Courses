#ifndef FILEHANDLER_H
#define FILEHANDLER_H
/////////////////////////////////////////////////////////////////////////////
// FileSystem.h - Support file and directory operations                    //
// ver 1.1                                                                 //
// Language:    Visual C++, Visual Studio 2008                             //
// Platform:    Dell Precision T7400, Quad core Xeons, Vista Ultimate, SP1 //
// Application: CSE687 - OOD, demonstration, Spring 2009                   //
// Author:      Jim Fawcett, CST 4-187, Syracuse University                //
//              (315) 443-3948, jfawcett@twcny.rr.com                      //
/////////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * This module provides two classes, File and FileHandler. The File class
 * supports opening text and binary files for either input or output.  The
 * File objects have names, get and put lines if text, get and put blocks
 * of bytes if binary, can be tested for operational state, cleared of errors,
 * and output File objects can be flushed to their streams.
 *
 * The FileHandler class supports converting relative paths to full paths,
 * getting filenames from a fully qualified filespec, e.g., path + filename,
 * getting and setting the current directory, and getting a vector of names
 * of files or directories in the current directory.
 *
 * Public Interface:
 * =================
 * File f(filespec,File::in,File::binary);
 * File g(filespec,File::out,File::binary);
 * while(f.isGood()) {
 *   block b = f.getBlock();
 *   g.putBlock(b);
 * }
 * FileHandler fh;
 * std::string path = fh.getFullPath(relativePath);
 * std::string name = fh.getFileName(relativePath);
 * std::string dir = fh.getCurrentDirectory();
 * fh.setCurrentDirectory(dir);
 * std::vector<std::string> files = fh.getFiles();
 * std::vector<std::string> dirs = fh.getDirectories();
 * 
 * Required Files:
 * ===============
 * FileSystem.h, FileSystem.cpp
 *
 * Build Command:
 * ==============
 * cl /EHa /DTEST_FILESYSTEM FileSystem.cpp
 *
 * Maintenance History:
 * ====================
 * ver 1.1 : 21 Feb 09
 * - added FileHandler::getFileSpecs(path,pattern) which returns fully qualified file names
 * - added FileHandler::getDirectorySpecs(path,pattern) which returns full path names
 * - changed getPath(fileSpec) to allow returning a relative path.
 *   You can always get the original behavior with: getFullPath(getPath(fileSpec))
 * ver 1.0 : 31 Jan 09
 * - first release
 */
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

namespace WinTools_Extracts
{
  class File
  {
  public:
    enum direction { in, out };
    enum type { text, binary };
    typedef char byte;
    typedef std::vector<byte> block;
    File(const std::string& filespec, direction dirn=File::out, type typ=File::text);
    ~File();
    std::string name();
    std::string getLine();
    void putLine(const std::string& line);
    size_t& blockSize();
    block getBlock();
    void putBlock(block);
    bool isGood();
    void clear();
    void flush();
    void close();
  private:
    std::string name_;
    size_t blockSize_;
    std::ifstream* pIStream;
    std::ofstream* pOStream;
    direction dirn_;
    type typ_;
  };

  inline std::string File::name() { return name_; }

  inline size_t& File::blockSize() { return blockSize_; }

  class FileHandler
  {
  public:
    FileHandler();
    std::string getFullPath(const std::string& filespec);
    std::string getPath(const std::string& filespec);
    char FileHandler::getSeperatorChar(const std::string& path);
    std::string getFileName(const std::string& filespec);
    std::string getCurrentDirectory();
    void setCurrentDirectory(const std::string& path);
    std::vector<std::string> getFiles(const std::string& pattern="*.*");
    std::vector<std::string> getFileSpecs(const std::string& path=".", const std::string& pattern="*.*");
    std::vector<std::string> getDirectories(const std::string& pattern="*.*");
    std::vector<std::string> getSubDirectorySpecs(const std::string& path=".", const std::string& pattern="*.*");
  private:
    static const int BufSize = 255;
    char buffer[BufSize];
    WIN32_FIND_DATAA FindFileData;
    WIN32_FIND_DATAA* pFindFileData;
  };

  inline FileHandler::FileHandler() : pFindFileData(&FindFileData) {}

}

#endif
