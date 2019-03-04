/////////////////////////////////////////////////////////////////////
//  Dependencies.cpp - Records file dependencies for each          //
//                     processed file                              //
//  ver 1.0                                                        //
//  Language:      Visual C++, Visual Studio 2017                  //
//  Platform:      Dell Latitude 5580, Windows 10                  //
//  Application:   CSE687 - OOD Project #2                         //
//  Author:        Junhao Shen, Syracuse University                //
//                 jshen18@syr.edu                                 //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Dependencies.h"
#include "../Parser/Parser.h"
#include "../Utilities/Utilities.h"
#include "../Tokenizer/Toker.h"
#include "../SemiExpression/Semi.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"

using namespace Lexer;
using namespace Utilities;
using Demo = Logging::StaticLogger<1>;
using namespace CodeAnalysis;

Dependencies::Dependencies() {}
Dependencies::~Dependencies() {}

//----< find files' dependencies >-----------------------------------------

#define Util StringHelper
using mapString = std::map<std::string, std::vector<std::string>>;

mapString Dependencies::findDependencies(std::vector<std::string> files)
{
	for (int i = 0; i < files.size(); ++i)
	{
		std::string fileSpec = FileSystem::Path::getFullFileSpec(files[i]);
		std::string msg = "Processing file " + fileSpec;
		std::vector<std::string> dependency;
		Util::title(msg);
		ConfigParseForCodeAnal configure;
		Parser* pParser = configure.Build();
		try
		{
			if (pParser)
			{
				if (!configure.Attach(files[i]))
				{
					std::string name = FileSystem::Path::getName(files[i]);
					std::cout << "\n  could not open file " << name << std::endl;
					continue;
				}
			}
			else
			{
				std::cout << "\n\n  Parser not built\n\n";
				return this->dependencies;
			}
			// now that parser is built, use it
			while (pParser->next())
				pParser->parse();
			std::cout << "\n";
			// show AST
			Repository* pRepo = Repository::getInstance();
			ASTNode* pGlobalScope = pRepo->getGlobalScope();
			// Filter statement and get those dependencies we want
			for (auto statement : pGlobalScope->statements_) {
				if (statement->size() == 3) {
					auto i = statement->begin();
					if (*i == "#") {
						i++;
						if (*i == "include") {
							i++;
							dependency.push_back(*i);
						}
					}
				}
			}
			this->dependencies[files[i]] = dependency;
		}
		catch (std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
			std::cout << "\n  exception thrown at line " << __LINE__;
		}
	}
	std::cout << "\n";
	return this->dependencies;
}


#ifdef TEST_DEPENDENCIES

//----< DEPENDENCIES TEST TUB >------------------------------------------

using namespace std;

int main()
{
	Dependencies depend;
	vector<string> files = { "Dependencies.cpp", "Dependencies.h" };
	map<string, vector<string>> dependencies = depend.findDependencies(files);

	Util::title("Test Dependencies");
	for (auto i = dependencies.begin(); i != dependencies.end(); i++) {
		std::cout << "\nFor " << i->first << ", Dependencies are: \n";
		for (auto item : i->second)
			std::cout << item << std::endl;
		std::cout << "\n\n";
	}

	return 0;
}

#endif

