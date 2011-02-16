/////////////////////////////////////////////////////////////////////////////
// GetIncludes.h - Process C++ files include statements                    //
// ver 1.0                                                                 //
// Language:    Visual C++, Visual Studio 2008                             //
// Platform:    Dell Precision T7400, Quad core Xeons, Vista Ultimate, SP1 //
// Application: CSE687 - OOD, demonstration, Spring 2009                   //
// Author:      Jim Fawcett, CST 4-187, Syracuse University                //
//              (315) 443-3948, jfawcett@twcny.rr.com                      //
/////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>
#include <iostream>
#include "GetIncludes.h"
#include "../FileSystemDemo/FileSystem.h"
using namespace WinTools_Extracts;

//----< show fully qualified names in Includes::vector of files >----------

void Includes::showFull(const vector& files, const std::string& msg)
{
  for(size_t i=0; i<files.size(); ++i)
    std::cout << "\n  " << msg.c_str() << files[i].c_str();
}
//----< show file names in Includes::vector of files >---------------------

void Includes::show(const vector& files, const std::string& msg)
{
  FileHandler fh;
  for(size_t i=0; i<files.size(); ++i)
    std::cout << "\n  " << msg.c_str() << fh.getFileName(files[i]).c_str();
}
//----< merge the contents of two Includes::vectors >----------------------

Includes::vector Includes::mergeFiles(const vector& f, const vector&g)
{
  vector sum(f.begin(),f.end());
  for(size_t i=0; i<g.size(); ++i)
    sum.push_back(g[i]);
  return sum;
}
//----< get included fileSpec from line with #include >--------------------

std::string Includes::getIncludedFileSpec(const std::string& line, includeType type)
{
  char startChar = '\"', endChar = '\"';
  if(type == system)
  {  
    startChar = '<';
    endChar = '>';
  }
  size_t start = line.find_first_of(startChar);
  if(start >= line.size())
    return "";
  size_t end = line.find_last_of(endChar);
  if(end >= line.size() || end < start)
    return "";
  return line.substr(start+1,end-start-1);
}
#ifdef TEST_GETINCLUDES

//----< test stub expects path on command, but will use default >----------

void main(int argc, char* argv[])
{
  std::cout << "\n  Demonstrating GetIncludes Processing";
  std::cout << "\n ======================================\n";

  FileHandler fh;
  Includes::vector files;
  if(argc == 1)
  {
    std::cout << "\n  path: " << fh.getFullPath(".") << std::endl;
    std::cout << "\n  found files:";
    Includes::vector cppfiles = fh.getFileSpecs(".", "*.cpp");
    Includes::vector hfiles = fh.getFileSpecs(".", "*.h");
    files = Includes::mergeFiles(cppfiles, hfiles);
    cppfiles = fh.getFileSpecs("../FileSystemDemo/", "*.cpp");
    files = Includes::mergeFiles(files,cppfiles);
    hfiles = fh.getFileSpecs("../FileSystemDemo/", "*.h");
    files = Includes::mergeFiles(files,hfiles);
    Includes::show(files, "  ");
  }
  else
  {
    std::cout << "\n  path: " << fh.getFullPath(argv[1]) << std::endl;
    std::cout << "\n  found files:";
    Includes::vector cppfiles = fh.getFileSpecs(argv[1],"*.cpp");
    Includes::vector hfiles = fh.getFileSpecs(argv[1],"*.h");
    files = Includes::mergeFiles(cppfiles, hfiles);
    Includes::show(files, "  ");
  }

  for(size_t i=0; i<files.size(); ++i)
  {
    std::cout << "\n\n  Processing file " << fh.getFileName(files[i]);
    File f(files[i],File::in);
    while(f.isGood())
    {
      std::string line = f.getLine();
      if(line.size() > 0 && line[0] == '#')
      {
        std::string temp = Includes::getIncludedFileSpec(line, Includes::system);
        if(temp.size() > 0)
          std::cout << "\n    system include: " << temp;
        temp = Includes::getIncludedFileSpec(line, Includes::local);
        if(temp.size() > 0)
        {
          std::cout << "\n    local include:  " << temp;
          FileHandler fh;
          std::cout << "\n      relative path: " << fh.getPath(temp);
          std::cout << "\n      full path: " << fh.getFullPath(fh.getPath(temp));
          std::cout << "\n      file: " << fh.getFileName(temp);
        }
      }
    }
  }
  std::cout << "\n\n";
}
#endif
