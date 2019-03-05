/////////////////////////////////////////////////////////////////////
//  Executive.cpp - Starter code for Project #2                    //
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
 * Executive package is the starter of the Proj #2, it invokes 4 packages
 * to get a Source Code Publisher for Projects: Loader, Dependencies,
 * Converter and Display
 *
 * Required Files:
 * ---------------
 * Executive.h, Executive.cpp
 * AbstrSynTree.h, AbstrSynTree.cpp
 * ActionsAndRules.h, ActionsAndRules.cpp
 * ConfigureParser.h, ConfigureParser.cpp
 * CodeUtilities.h, CodeUtilities.cpp
 * Converter.h, Converter.cpp
 * Dependencies.h, Dependencies.cpp
 * FileSystem.h, FileSystem.cpp
 * GrammarHelpers.h, GrammarHelpers.cpp
 * ITokenCollection.h
 * Loader.h, Loader.cpp
 * Logger.h, Logger.cpp
 * Parser.h, Parser.cpp
 * ScopeStack.h, ScopeStack.cpp
 * Semi.h, Semi.cpp
 * StringUtilities.h, StringUtilities.cpp
 * Toker.h, Toker.cpp
 * Utilities.h, Utilities.cpp
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 4 Mar 2019
 * - first release
 *
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../Utilities/CodeUtilities.h"
#include "../Utilities/StringUtilities.h"
#include "../FileSystem/FileSystem.h"
#include "../Loader/Loader.h"
#include "../Dependencies/Dependencies.h"
#include "../Parser/Parser.h"
#include "../Utilities/Utilities.h"
#include "../Tokenizer/Toker.h"
#include "../SemiExpression/Semi.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../Converter/Converter.h"
#include "../Display/Display.h"

using namespace std;
using namespace Utilities;
using namespace FileSystem;
using namespace Lexer;
using namespace CodeAnalysis;
using namespace CodeUtilities;
//using Demo = Logging::StaticLogger<1>;

int main(int argc, char** argv)
{
	//Prologue
	cout << "/////////////////////////////////////////////////////////////////////////////\n"
		 << "// CSE687 Project #2 - Source Code Publisher for Projects                  //\n"
		 << "// ver 1.0                                                                 //\n"
		 << "// ----------------------------------------------------------------------- //\n"
		 << "// copyright @Junhao Shen, 2019                                            //\n"
		 << "// All rights granted provided that this notice is retained                //\n"
		 << "// ----------------------------------------------------------------------- //\n"
		 << "// Language:    Visual C++, Visual Studio 2017                             //\n"
		 << "// Platform:    Dell Latitude 5580, Core i7, Windows 10                    //\n"
		 << "// Application: Project #2, 2019                                           //\n"
		 << "// Author:      Junhao Shen                                                //\n"
		 << "//              (315)480-4274, jshen18@syr.edu                             //\n"
		 << "/////////////////////////////////////////////////////////////////////////////\n\n";

	//Executive: Starter code for Project #2
	cout << "  Executive Package";
	cout << "\n=============================================================";
	cout << "\n  starter code for proj #2, will call Loader, Dependencies, Convert and Display in sequence";
	cout << "\n\n  Press key to continue \n\n";
	getchar();

	//Loader: find and load files from file system
	cout << "  Loader Package";
	cout << "\n=============================================================";
	cout << "\n  accept command parameters to find files fullpath";
	cout << "\n\n  Press key to continue ";
	getchar();
	DirExplorerN dir;
	vector<string> files = dir.loadFiles(argc, argv);
	cout << "\n\n  Find all *.cpp & *.h File:" << endl;
	for (auto str : files)
		std::cout << "  --  " << str << std::endl;
	
	//Dependencies: Records file dependencies for each processed file
	cout << "\n\n  Dependencies Package";
	cout << "\n=============================================================";
	cout << "\n  records file dependencies for each processed file";
	cout << "\n\n  Press key to continue ";
	getchar();
	Dependencies depend;
	map<string, vector<string>> dependencies = depend.findDependencies(files);
	for (auto i = dependencies.begin(); i != dependencies.end(); i++) {
		std::cout << "\n  For " << i->first << ", Dependencies are: \n";
		for (auto item : i->second)
			std::cout << "  " << item << std::endl;
	}
	
	//Converter: accept filenames to convert those files to html
	cout << "\n\n  Converter Package";
	cout << "\n=============================================================";
	cout << "\n  accept filenames to convert those files to html";
	cout << "\n\n  Press key to continue ";
	getchar();
	Convert convert;
	vector<vector<vector<int>>> funcPos(files.size());
	vector<vector<vector<int>>> classPos(files.size());
	std::cout << "\n\n  1. getFuncClass: get links to all the files in the directory tree, on which it depends" << std::endl;
	convert.getFuncClass(files, funcPos, classPos);
	std::cout << "\n\n  2. convertToHtml: convert cpp/h files to html" << std::endl;
	convert.convertToHtml(files, dependencies, funcPos, classPos);
	
	//Display: display converted html pages in user's browser
	cout << "\n\n  Display Package";
	cout << "\n=============================================================";
	cout << "\n  display converted html pages in user's browser";
	cout << "\n\n  Press key to continue ";
	getchar();
	Process process;
	string appPath = argv[argc - 1];
	process.pop_out(files, appPath);
	

	return 0;
}

