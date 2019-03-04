#pragma once
/////////////////////////////////////////////////////////////////////
//  Dependencies.h - Records file dependencies for each processed  //
//                   file                                          //
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
 * Dependency creates a class "Dependencies", in order to find and
 * record the file dependencies for specific files. it's core function
 * is findDependencies, which accepts a vector of file's name and output
 * a map that links file's name and its dependencies.
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
 * ver 1.0 : 4 Mar 2019
 * - first release
 *
*/
#include <vector>
#include <string>
#include <map>

class Dependencies
{
	using mapString = std::map<std::string, std::vector<std::string>>;
public:
	Dependencies();
	~Dependencies();
	mapString findDependencies(std::vector<std::string> files);
private:
	mapString dependencies;
};