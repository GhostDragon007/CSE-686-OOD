/////////////////////////////////////////////////////////////////////
//  Loader.cpp - finding and loading all the files for conversion  //
//  ver 1.0                                                        //
//  Language:      Visual C++, Visual Studio 2017                  //
//  Platform:      Dell Latitude 5580, Windows 10                  //
//  Application:   CSE687 - OOD Project #2                         //
//  Author:        Junhao Shen, Syracuse University                //
//                 jshen18@syr.edu                                 //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <regex>
#include "Loader.h"
#include "../Utilities/CodeUtilities.h"
#include "../Utilities/StringUtilities.h"
#include "../FileSystem/FileSystem.h"

using namespace Utilities;
using namespace FileSystem;
using namespace CodeUtilities;

//----< two constructors >-----------------------------------------

DirExplorerN::DirExplorerN(){}

DirExplorerN::DirExplorerN(const std::string& path) : path_(path)
{
	patterns_.push_back("*.*");
}
//----< add specified patterns for selecting file names >----------

void DirExplorerN::addPattern(const std::string& patt)
{
	if (patterns_.size() == 1 && patterns_[0] == "*.*")
		patterns_.pop_back();
	patterns_.push_back(patt);
}
//----< set option to recusively walk dir tree >-------------------

void DirExplorerN::recurse(bool doRecurse)
{
	recurse_ = doRecurse;
}
//----< start Depth First Search at path held in path_ >-----------

void DirExplorerN::search(const std::string& regexes_)
{
	find(path_, regexes_);
}
//----< search for directories and their files >-------------------
/*
  Recursively finds all the dirs and files on the specified path,
  executing doDir when entering a directory and doFile when finding a file
*/
void DirExplorerN::find(const std::string& path, const std::string& regexes_)
{
	// show current directory

	std::string fpath = FileSystem::Path::getFullFileSpec(path);
	doDir(fpath);

	for (auto patt : patterns_)
	{
		std::vector<std::string> files = FileSystem::Directory::getFiles(fpath, patt);
		for (auto f : files)
		{
			std::string fullPath = fpath + "\\" + f;
			std::regex r(regexes_);
			if (std::regex_match(f, r)) { // find the files that satisfy the regex
				std::string newFile = "../ConvertedPages/";
				newFile = FileSystem::Path::getFullFileSpec(newFile);
				this->files.push_back(fullPath);
				doFile(f, fullPath);  // show each file in current directory
			}
		}
	}

	std::vector<std::string> dirs = FileSystem::Directory::getDirectories(fpath);
	for (auto d : dirs)
	{
		if (d == "." || d == "..")
			continue;
		std::string dpath = fpath + "\\" + d;
		if (recurse_)
		{
			find(dpath, regexes_);   // recurse into subdirectories
		}
		else
		{
			doDir(dpath);  // show subdirectories
		}
	}
}
//----< an application changes to enable specific file ops >-------

void DirExplorerN::doFile(const std::string& filename, const std::string& fullPath)
{
	++fileCount_;
	std::cout << "\n  --   " << filename;
}
//----< an application changes to enable specific dir ops >--------

void DirExplorerN::doDir(const std::string& dirname)
{
	++dirCount_;
	std::cout << "\n  ++ " << dirname;
}
//----< return number of files processed >-------------------------

size_t DirExplorerN::fileCount()
{
	return fileCount_;
}
//----< return number of directories processed >-------------------

size_t DirExplorerN::dirCount()
{
	return dirCount_;
}
//----< show final counts for files and dirs >---------------------

void DirExplorerN::showStats()
{
	std::cout << "\n\n  processed " << fileCount_ << " files in " << dirCount_ << " directories";
}

ProcessCmdLine::Usage customUsage()
{
	std::string usage;
	usage += "\n  Command Line: path [/option]* [/pattern]*";
	usage += "\n    path is relative or absolute path where processing begins";
	usage += "\n    [/option]* are one or more options of the form:";
	usage += "\n      /s - walk directory recursively";
	//usage += "\n      /h - hide empty directories";
	//usage += "\n      /a - on stopping, show all files in current directory";
	usage += "\n    [pattern]* are one or more pattern strings of the form:";
	usage += "\n      *.h *.cpp *.cs *.txt or *.*";
	usage += "\n";
	return usage;
}

//----< find and load files from file system >----------------------
//DirExplorer: accept command parameters to find files fullpath

std::vector<std::string> DirExplorerN::loadFiles(int argc, char *argv[])
{
	ProcessCmdLine pcl(argc, argv);
	pcl.usage(customUsage());

	preface("Command Line: ");
	pcl.showCmdLine();
	putline();
	std::string regs = argv[5];
	std::vector<std::string> result;

	if (pcl.parseError())
	{
		pcl.usage();
		std::cout << "\n\n";
		return result;
	}

	DirExplorerN de(pcl.path());
	for (auto patt : pcl.patterns())
	{
		de.addPattern(patt);
	}

	if (pcl.hasOption('s'))
	{
		de.recurse();
	}

	de.search(regs);
	de.showStats();
	result = de.files;
	if (result.empty())
		std::cout << "\n\nError Message: No file has been found!" << std::endl;
	return result;
}


#ifdef TEST_LOADER
//----< LOADER TEST STUB >-------------------
/*
	Command line parameters:
	argc = 7;
	argv = {"D:\\little shen\\Syracuse\\CSE 687\\Code\\Project2Starter\\x64\\Debug\\Loader.exe",
			"..",
			"/s",
			"*.cpp",
			"*.h",
			"^Loader*.[a-zA-Z]*$",
			"C:/Users/47221/AppData/Local/Google/Chrome/Application/chrome.exe"};
*/
int main(int argc, char** argv)
{
	Title("Test Loader: accept command parameters to find files fullpath");

	//Start to test 
	DirExplorerN dir;
	std::vector<std::string> fileName = dir.loadFiles(argc, argv);
	std::cout << "\n\n--------------------TEST DIREXPLORER--------------------\n" << std::endl
		<< "Find all *.cpp & *.h File:" << std::endl;
	for (auto str : fileName)
		std::cout << "  --  " << str << std::endl;
	std::cout << "\n\n--------------------END TEST DIREXPLORER--------------------\n" << std::endl;
	std::cout << "\n\n";
	return 0;
}
#endif