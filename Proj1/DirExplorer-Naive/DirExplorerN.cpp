/////////////////////////////////////////////////////////////////////
// DirExplorerN.cpp - Naive directory explorer                     //
// ver 1.2                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
// Modified by Junhao Shen, Spring 2019                            //
/////////////////////////////////////////////////////////////////////
  // only compile the following when defined

#include "DirExplorerN.h"

using namespace Utilities;
using namespace FileSystem;

DirExplorerN::DirExplorerN() {}

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
				this->vec_fullPath.push_back(fullPath);
				this->vec_fileName.push_back(f);
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

//----< Do DirExplorer >-------------------
//DirExplorer: accept command parameters to find files fullpath

std::vector<std::vector<std::string>> DirExplorerN::doDirExplore(int argc, char *argv[]) {
	Title("DirExplorer: accept command parameters to find files fullpath");

	ProcessCmdLine pcl(argc, argv);
	pcl.usage(customUsage());

	preface("Command Line: ");
	pcl.showCmdLine();
	putline();
	std::vector<std::vector<std::string>> res;
	std::string regs = argv[5];

	if (pcl.parseError())
	{
		pcl.usage();
		std::cout << "\n\n";
		return res;
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
	res.push_back(de.vec_fileName);
	res.push_back(de.vec_fullPath);
	if (res[0].empty())
		std::cout << "\n\nError Message: No file has been found!" << std::endl;
	return res;
}

//----< DIREXPLORER TEST STUB >-------------------
#ifdef TEST_DIREXPLORERN

int main(int argc, char *argv[])
{
	DirExplorerN dir = DirExplorerN();
	std::vector<std::vector<std::string>> res = dir.doDirExplore(argc, argv);
	std::vector <std::string> fileName = res[1];
	//std::vector <std::string> path = res[1];
	std::cout << "\n\n--------------------TEST DIREXPLORER--------------------\n" << std::endl
		<< "Find all *.cpp & *.h File:" << std::endl;
	for (auto str : fileName)
		std::cout << "  --  " << str << std::endl;
	std::cout << "\n\n--------------------END TEST DIREXPLORER--------------------\n" << std::endl;
	std::cout << "\n\n";
	return 0;
}
#endif