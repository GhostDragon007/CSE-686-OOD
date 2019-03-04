/////////////////////////////////////////////////////////////////////
//  Executive.cpp - Starter code for Project #2                    //
//  ver 1.0                                                        //
//  Language:      Visual C++, Visual Studio 2017                  //
//  Platform:      Dell Latitude 5580, Windows 10                  //
//  Application:   CSE687 - OOD Project #2                         //
//  Author:        Junhao Shen, Syracuse University                //
//                 jshen18@syr.edu                                 //
/////////////////////////////////////////////////////////////////////

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
	//Loader: find and load files from file system
	DirExplorerN dir;
	vector<string> files = dir.loadFiles(argc, argv);

	//Dependencies: Records file dependencies for each processed file
	Dependencies depend;
	map<string, vector<string>> dependencies = depend.findDependencies(files);

	//Converter: accept filenames to convert those files to html
	Convert convert;
	std::vector<std::vector<std::vector<int>>> funcPos(files.size());
	std::vector<std::vector<std::vector<int>>> classPos(files.size());
	convert.getFuncClass(files, funcPos, classPos);
	convert.convertToHtml(files, dependencies, funcPos, classPos);

	//Display: display converted html pages in user's browser
	Process process;
	string appPath = argv[argc - 1];
	process.pop_out(files, appPath);

	return 0;
}

