/////////////////////////////////////////////////////////////////////////////
// Converter.h - accept a vector of filenames to convert those files to    //
//               html files                                                //
// ver 1.1                                                                 //
// Language:    Visual C++, Visual Studio 2019                             //
// Platform:    Dell Latitude , Core i7, Windows 10                        //
// Application: CSE687 - OOD Project #2                                    //
// Author:      Junhao Shen                                                //
//              (315)480-4274, jshen18@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////

/*
 * Package Operations:
 * -------------------
 * Converter creates a class "Convert", in order to transform cpp/h files
 * into html files, along with inserting dependencies, inserting <span>
 * between functions and classes to make them controllable to either be
 * seen or not by buttons.
 *
 * Required Files:
 * ---------------
 * Dependencies.h, Dependencies.cpp
 * AbstrSynTree.h, AbstrSynTree.cpp
 * ActionsAndRules.h, ActionsAndRules.cpp
 * ConfigureParser.h, ConfigureParser.cpp
 * FileSystem.h, FileSystem.cpp
 * GrammarHelpers.h, GrammarHelpers.cpp
 * ITokenCollection.h
 * Logger.h, Logger.cpp
 * Parser.h, Parser.cpp
 * ScopeStack.h, ScopeStack.cpp
 * Semi.h, Semi.cpp
 * Toker.h, Toker.cpp
 * Utilities.h, Utilities.cpp
 *
 * Maintenance History:
 * --------------------
 * ver 1.1 : 4 Mar 2019
 * - modify 
 * ver 1.0 : 1 Feb 2019
 * - first release
 *
*/

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

class Convert
{
public:
	Convert();
	~Convert();
	void getFuncClass(std::vector<std::string>& files,
		std::vector<std::vector<std::vector<int>>>& funcPos, std::vector<std::vector<std::vector<int>>>& classPos);
	void convertToHtml(std::vector<std::string>& files, std::map<std::string, std::vector<std::string>>& dependencies,
		std::vector<std::vector<std::vector<int>>>& funcPos, std::vector < std::vector<std::vector<int>>>& classPos);
};

