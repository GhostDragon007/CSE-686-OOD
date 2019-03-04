#pragma once
/////////////////////////////////////////////////////////////////////
//  Loader.h - finding and loading all the files for conversion    //
//  ver 1.0                                                        //
//  Language:      Visual C++, Visual Studio 2017                  //
//  Platform:      Dell Latitude 5580, Windows 10                  //
//  Application:   CSE687 - OOD Project #2                         //
//  Author:        Junhao Shen, Syracuse University                //
//                 jshen18@syr.edu                                 //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * Loader uses a class, "DirExplorer", which modifies from Prof.
 * Fawcett, that executes a depth first search of a directory tree 
 * rooted at a specified path. Each time it enters a directory, it 
 * invokes its member function doDir, and for every file in that 
 * directory, it invokes doFile.
 *
 * We call this a "Naive Directory Explorer" because, while it carries
 * out its assigned responsibilities well, there is no way to change
 * what its doDir and doFile functions do, without changing the class
 * itself.  It would be much better to provide a mechanism to allow
 * a using application to supply this processing without changing
 * the Directory Navigator.
 *
 *
 * We'll be using this solution to illustrate techniques for building
 * flexible software.
 *
 * Required Files:
 * ---------------
 * Loader.h, Loader.cpp
 * FileSystem.h, FileSystem.cpp      // Directory and Path classes
 * StringUtilities.h                 // Title function
 * CodeUtilities.h                   // ProcessCmdLine class
 *
 * Maintenance History:
 * --------------------
 * ver 1.4 :  4 Mar 2019
 * - Add loadFile method which accepts two parameters, one is char* []
 *   which contains the files' position, name pattern, regular expression
 *   and explorer's position. And another one is the length of this array.
 * ver 1.3 : 19 Aug 2018
 * - Removed some options to make this version simple.  Those are
 *   implemented in the more advanced navigators, presented here.
 * ver 1.2 : 17 Aug 2018
 * - Moved method definitions to inlines, below the class declaration.
 * ver 1.1 : 16 Aug 2018
 * - Made no recursion default, added option /s for recursion.
 * ver 1.0 : 11 Aug 2018
 * - first release
 *
*/

#include <vector>

namespace FileSystem
{
	class DirExplorerN
	{
	public:
		using patterns = std::vector<std::string>;

		static std::string version() { return "ver 1.3"; }

		DirExplorerN(const std::string& path);
		DirExplorerN();

		// set options for analysis

		void addPattern(const std::string& patt);
		void recurse(bool doRecurse = true);

		// conduct depth first search

		void search(const std::string& regexes_);
		void find(const std::string& path, const std::string& regexes_);

		// define what happens when a file or dir is encountered

		void doFile(const std::string& filename, const std::string& fullPath);
		void doDir(const std::string& dirname);

		// extract traversal statistics 

		size_t fileCount();
		size_t dirCount();
		void showStats();
		std::vector<std::string> loadFiles(int argc, char *argv[]);

	private:
		std::string path_;
		patterns patterns_;
		size_t dirCount_ = 0;
		size_t fileCount_ = 0;
		bool recurse_ = false;
		std::vector<std::string> files;
	};

	//----< construct DirExplorerN instance with default pattern >-----


}

