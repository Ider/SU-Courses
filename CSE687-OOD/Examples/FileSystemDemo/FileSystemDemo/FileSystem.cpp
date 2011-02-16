/////////////////////////////////////////////////////////////////////////////
// FileSystem.cpp - Support file and directory operations                  //
// ver 1.1                                                                 //
// Language:    Visual C++, Visual Studio 2008                             //
// Platform:    Dell Precision T7400, Quad core Xeons, Vista Ultimate, SP1 //
// Application: CSE687 - OOD, demonstration, Spring 2009                   //
// Author:      Jim Fawcett, CST 4-187, Syracuse University                //
//              (315) 443-3948, jfawcett@twcny.rr.com                      //
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "FileSystem.h"

using namespace WinTools_Extracts;

//----< File constructor opens file stream >-------------------------------

File::File(const std::string& filespec, direction dirn, type typ) 
    : name_(filespec), blockSize_(1024), pIStream(0), pOStream(0), dirn_(dirn), typ_(typ)
{
  if(dirn == in)
  {
    pIStream = new std::ifstream;
    if(typ == binary)
      pIStream->open(filespec.c_str(), std::ios::in | std::ios::binary);
    else
      pIStream->open(filespec.c_str(), std::ios::in);
  }
  else
  {
    pOStream = new std::ofstream;
    if(typ == binary)
      pOStream->open(filespec.c_str(), std::ios::out | std::ios::binary);
    else
      pOStream->open(filespec.c_str(), std::ios::out);
  }
}
//----< File destructor closes file stream >-------------------------------

File::~File() 
{ 
  if(pIStream)
  {
    pIStream->close(); 
    delete pIStream;
  }
  if(pOStream)
  {
    pOStream->close();
    delete pOStream; 
  }
}
//----< reads one line of a text file >------------------------------------

std::string File::getLine()
{
  if(typ_ == binary)
    throw std::exception("binary file");
  const int BufSize = 255;
  char buffer[BufSize];
  pIStream->getline(buffer,BufSize);
  return std::string(buffer);
}
//----< writes one line of a text to a file >------------------------------

void File::putLine(const std::string& s)
{
  if(typ_ == binary)
    throw std::exception("binary file");
  for(size_t i=0; i<s.size(); ++i)
    pOStream->put(s[i]);
  pOStream->flush();
}
//----< reads a block of bytes from binary file >--------------------------

File::block File::getBlock()
{
  block blk;
  if(pIStream)
  {
    for(size_t i=0; i<blockSize(); ++i)
    {
      byte b = pIStream->get();
      if(pIStream->good())
        blk.push_back(b);
      else
        break;
    }
  }
  return blk;
}
//----< writes a block of bytes to binary file >---------------------------

void File::putBlock(File::block blk)
{
  if(!pOStream->good())
    return;
  for(size_t i=0; i<blk.size(); ++i)
  {
    pOStream->put(blk[i]);
  }
}
//----< tests for error free stream state >--------------------------------

bool File::isGood()
{
  if(pIStream)
    return pIStream->good();
  if(pOStream)
    return pOStream->good();
  return false;
}
//----< flushes output stream to its file >--------------------------------

void File::flush()
{
  if(pOStream)
    pOStream->flush();
  if(pOStream)
    return;
}
//----< clears error state enabling operations again >---------------------

void File::clear()
{
  if(pIStream)
    pIStream->clear();
  if(pOStream)
    pOStream->clear();
}
//----< close file handle >------------------------------------------------

void File::close()
{
  File::flush();
  if(pIStream)
    pIStream->close();
  if(pOStream)
    pOStream->close();
}
//----< convert relative path to full path >-------------------------------

std::string FileHandler::getFullPath(const std::string& filespec)
{
  ::GetFullPathNameA(filespec.c_str(),BufSize,buffer,NULL);
  return std::string(buffer);
}
//----< extract, possibly relative, path from filespec >-------------------

std::string FileHandler::getPath(const std::string& filespec)
{
  std::string temp(filespec);
  size_t pos = temp.find_last_of('\\');
  if(pos >= temp.size())
  {
    pos = temp.find_last_of('/');
    if(pos >= temp.size())
      return ".";
  }
  return temp.substr(0,pos+1);
}
//----< get file name part of path string >--------------------------------

std::string FileHandler::getFileName(const std::string& filespec)
{
  char* pTempBuffer = 0;
  ::GetFullPathNameA(filespec.c_str(),BufSize,buffer,(LPSTR*)&pTempBuffer);
  if(pTempBuffer)
    return std::string(pTempBuffer);
  return std::string("");
}
//----< return name of the current directory >-----------------------------

std::string FileHandler::getCurrentDirectory()
{
  ::GetCurrentDirectoryA(BufSize,buffer);
  return std::string(buffer);
}
//----< change the current directory to path >-----------------------------

void FileHandler::setCurrentDirectory(const std::string& path)
{
  ::SetCurrentDirectoryA(path.c_str());
}
//----< get directory seperator character >--------------------------------

char FileHandler::getSeperatorChar(const std::string& path)
{
  if(path.find_first_of('\\') < path.size())
    return '\\';
  else if(path.find_first_of('/') < path.size())
    return '/';
  return '\\';
}
//----< get fully qualified names of files >-------------------------------

std::vector<std::string> FileHandler::getFileSpecs(
  const std::string& inpath, 
  const std::string& inpattern
)
{
  std::string path = getFullPath(inpath);
  char sepChar = getSeperatorChar(path);
  if(path.size() > 0)
  {
    char lastChar = path[path.size()-1];
    if(lastChar != sepChar)
      path += sepChar;
  }
  std::string pattern = path + inpattern;
  std::vector<std::string> files;
  HANDLE hFindFile = ::FindFirstFileA(pattern.c_str(),pFindFileData);
  if(hFindFile != INVALID_HANDLE_VALUE)
  {
    if(!(pFindFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
      files.push_back(path + pFindFileData->cFileName);
    while(::FindNextFileA(hFindFile,pFindFileData))
    {
      if(!(pFindFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        files.push_back(path + pFindFileData->cFileName);
    }
  }
  ::FindClose(hFindFile);
  return files;
}
//----< get fully qualified names of subdirectories >----------------------

std::vector<std::string> FileHandler::getSubDirectorySpecs(
  const std::string& inpath,
  const std::string& inpattern
)
{
  std::string path = getFullPath(inpath);
  for(size_t i=0; i<path.size(); ++i)
    if(path[i] == '/')
      path[i] = '\\';
  if(path.size() > 0)
  {
    char lastChar = path[path.size()-1];
    if(lastChar != '\\')
      path += '\\';
  }
  std::string pattern = path + inpattern;
  std::vector<std::string> files;
  HANDLE hFindFile = ::FindFirstFileA(pattern.c_str(),pFindFileData);
  if(hFindFile != INVALID_HANDLE_VALUE)
  {
    if(pFindFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      files.push_back(path + pFindFileData->cFileName);
    while(::FindNextFileA(hFindFile,pFindFileData))
    {
      if(pFindFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        files.push_back(path + pFindFileData->cFileName);
    }
  }
  ::FindClose(hFindFile);
  return files;
}
//----< get names of all the files matching pattern (path:name) >----------

std::vector<std::string> FileHandler::getFiles(const std::string& pattern)
{
  std::vector<std::string> files;
  HANDLE hFindFile = ::FindFirstFileA(pattern.c_str(),pFindFileData);
  if(hFindFile != INVALID_HANDLE_VALUE)
  {
    if(!(pFindFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
      files.push_back(pFindFileData->cFileName);
    while(::FindNextFileA(hFindFile,pFindFileData))
    {
      if(!(pFindFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
      files.push_back(pFindFileData->cFileName);
    }
  }
  ::FindClose(hFindFile);
  return files;
}
//----< get names of all directories matching pattern (path:name) >--------

std::vector<std::string> FileHandler::getDirectories(const std::string& pattern)
{
  std::vector<std::string> dirs;
  HANDLE hFindFile = ::FindFirstFileA(pattern.c_str(),pFindFileData);
  if(hFindFile != INVALID_HANDLE_VALUE)
  {
    if(pFindFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      dirs.push_back(pFindFileData->cFileName);
    while(::FindNextFileA(hFindFile,pFindFileData))
    {
      if(pFindFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      dirs.push_back(pFindFileData->cFileName);
    }
  }
  ::FindClose(hFindFile);
  return dirs;
}
//----< test stub >--------------------------------------------------------

#ifdef TEST_FILESYSTEM

void title(const std::string& title, char ch='=')
{
  std::cout << "\n  " << title;
  std::cout << "\n " << std::string(title.size()+2, ch);
}
int main(int argc, char* argv[])
{
  title("Demonstrate FileHandler class");

  // Display contents of current directory

  FileHandler fh;
  std::vector<std::string> tempfiles = fh.getFileSpecs("c:\\temp", "*.*");
  if(tempfiles.size() > 0)
  {
    std::cout << "\n  first file found in C:\\temp: " << tempfiles[0];
    std::cout << "\n  its path: " << fh.getPath(tempfiles[0]);
    std::cout << "\n  its name: " << fh.getFileName(tempfiles[0]) << std::endl;
  }
  std::cout << "\n  current directory is:\n    " << fh.getCurrentDirectory();
  std::cout << "\n  it contains files:";
  std::vector<std::string> currfiles = fh.getFiles();
  for(size_t i=0; i<currfiles.size(); ++i)
    std::cout << "\n    " << currfiles[i].c_str();
  std::cout << "\n  and contains directories:";
  std::vector<std::string> currdirs = fh.getDirectories();
  for(size_t i=0; i<currdirs.size(); ++i)
    std::cout << "\n    " << currdirs[i].c_str();
  std::cout << "\n";

  // Display contents of non-current directory

  std::cout << "\n  files residing in C:/temp are:";
  currfiles = fh.getFiles("c:/temp/*");
  for(size_t i=0; i<currfiles.size(); ++i)
    std::cout << "\n    " << currfiles[i].c_str();
  std::cout << "\n";
  std::cout << "\n  directories residing in C:/temp are:";
  currdirs = fh.getDirectories("c:/temp/*");
  for(size_t i=0; i<currdirs.size(); ++i)
    std::cout << "\n    " << currdirs[i].c_str();
  std::cout << "\n";

  std::cout << "\n  filespecs residing in C:/temp are:";
  currfiles = fh.getFileSpecs("c:/temp/");
  for(size_t i=0; i<currfiles.size(); ++i)
    std::cout << "\n    " << currfiles[i].c_str();
  std::cout << "\n";
  std::cout << "\n  directoryspecs residing in C:/temp are:";
  currdirs = fh.getSubDirectorySpecs("c:/temp/");
  for(size_t i=0; i<currdirs.size(); ++i)
    std::cout << "\n    " << currdirs[i].c_str();
  std::cout << "\n";

  // copy binary file from one directory to another

  File me("../debug/filesystemdemo.exe", File::in, File::binary);
  std::cout << "\n  copying " << me.name().c_str() << " to c:/temp";
  if(!me.isGood())
  {
    std::cout << "\n  can't open executable\n";
    std::cout << "\n  looking for:\n  ";
    std::cout << fh.getFullPath(me.name()) << "\n";
  }
  else
  {
    me.blockSize() = 32768;
    File you("c:/temp/fileSystemdemo.exe", File::out, File::binary);
    if(you.isGood())
    {
      while(me.isGood())
      {
        File::block b = me.getBlock();
        std::cout << "\n    reading block of " << b.size() << " bytes";
        you.putBlock(b);
        std::cout << "\n    writing block of " << b.size() << " bytes"; 
      }
      std::cout << "\n";
    }
  }

  title("Demonstrate File class operations", '=');
  std::cout << "\n";

  std::vector<std::string> files;
  if(argc == 1)
  {
    std::cout << "\n\n  Please enter, on the command line, a filename to process.\n";
  }

  // save some filespecs of text files in a vector for File demonstrations

  for(int i=1; i<argc; ++i)
  {
    files.push_back(argv[i]);
  }
  files.push_back("FileSystem.cpp");
  files.push_back("../FileSystemDemo/FileSystem.cpp"); // file from project directory
  files.push_back("../debug/test.txt");  // file in executable's debug directory
  files.push_back("foobar");             // doesn't exist

  // open each file and display a few lines of text

  for(size_t i=0; i<files.size(); ++i)
  {
    File file(files[i],File::in);
    if(!file.isGood())
    {
      std::cout << "\n  Can't open file " << file.name();
      std::cout << "\n  Here's what the program can't find:\n  " << fh.getFullPath(file.name()); 
      continue;
    }
    std::string temp = std::string("Processing file ") + files[i];
    title(temp, '-');
    for(int j=0; j<10; ++j)
    {
      if(!file.isGood())
        break;
      std::cout << "\n  " << file.getLine().c_str();
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  // read text file and write to another text file

  title("writing to c:/temp/test.txt", '-');
  File in("../debug/test.txt",File::in);
  File out("c:/temp/test.txt",File::out);
  while(in.isGood())
  {
    std::string temp = in.getLine();
    std::cout << "\n  " << temp.c_str();
    out.putLine(temp);
    out.putLine("\n");
  }
  std::cout << "\n\n";
}
#endif
