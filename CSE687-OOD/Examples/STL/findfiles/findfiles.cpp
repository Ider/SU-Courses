////////////////////////////////////////////////////////////////////
// findfiles.cpp - demonstrate use of STL containers
//

#include <iostream> 
#include <iomanip>
#include <set>
#include <map>
#include <list>
#include <string>
#include <windows.h>

using namespace std;

typedef set<string>::iterator iPath;

class filefinder {

  set<string> path;
  map< string,list<iPath> > files;

};

// prints information about a file
void PrintFindData(WIN32_FIND_DATA *findData, set<string> &sos)
{	
	cout << setw(18);
	cout << findData->cFileName;
	cout << "\t(" << findData->nFileSizeLow << ")";
	cout << endl;
  sos.insert(findData->cFileName);
}

// Recursively lists directories
void ListDirectoryContents(string dirName, 
	string fileMask, set<string> &sos)
{
	char *fileName;
	char curDir[256];
	char fullName[256];
	HANDLE fileHandle;
	WIN32_FIND_DATA findData;

	// save current dir so it can restore it
	if( !GetCurrentDirectory( 256, curDir) ) 
		return;
	
	// if the directory name is neither . or .. then
	// change to it, otherwise ignore it
	if( dirName != "." && dirName != ".." )
	{
		if( !SetCurrentDirectory( dirName.c_str() ) ) 
			return;
	}
	else 
		return;

	// print out the current directory name
	if( !GetFullPathName( fileMask.c_str(), 256, fullName, &fileName ) )
		return;
	cout << endl << "  Directory - " << fullName << endl;

	// Loop through all files in the directory
	fileHandle = FindFirstFile( fileMask.c_str(),	&findData );
	while ( fileHandle != INVALID_HANDLE_VALUE )
	{
		// If the name is a directory, recursively walk it.
    // Otherwise print the file's data

		if( findData.dwFileAttributes &	FILE_ATTRIBUTE_DIRECTORY )

			ListDirectoryContents( findData.cFileName, fileMask, sos );
		else
			PrintFindData( &findData, sos );

  		// loop thru remaining entries in the dir
		if (!FindNextFile( fileHandle, &findData ))
			break;
 	}
	
	// clean up and restore directory
	FindClose( fileHandle );
	SetCurrentDirectory( curDir );

  // print out the current directory name
	if( !GetFullPathName( fileMask.c_str(), 256, fullName, &fileName ) ) 
		return;
	cout << endl << "  Directory - " << fullName << endl;

}

int main(int argc, char *argv[])
{
	char	curDir[ 256 ];

	if( !GetCurrentDirectory( 256, curDir ) )
	{
		cerr << "Couldn't get the current directory." 
			<< endl;
		return( 1 );
	}

	// List all files, starting with the 
	// current directory

  set<string> sos;
  ListDirectoryContents( curDir, "*.*" , sos);

  cout << "\n  sorted list of all files:\n";
  set<string>::iterator si;
  for(si = sos.begin(); si != sos.end(); si++)
    cout << "    " << *si << endl;

  return( 0 );
}
