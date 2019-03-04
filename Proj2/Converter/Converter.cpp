/////////////////////////////////////////////////////////////////////////////
// Converter.cpp - accept a vector of filenames to convert those files to  //
//                 html files                                              //
// ver 1.1                                                                 //
// Language:    Visual C++, Visual Studio 2019                             //
// Platform:    Dell Latitude , Core i7, Windows 10                        //
// Application: CSE687 - OOD Project #2                                    //
// Author:      Junhao Shen                                                //
//              (315)480-4274, jshen18@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////

#include "Converter.h"
#include <iostream>
#include "../Utilities/StringUtilities.h"
#include "../Utilities/CodeUtilities.h"
#include "../FileSystem/FileSystem.h"
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

Convert::Convert() {}
Convert::~Convert() {}

//----< get links to all the files in the directory tree, on which it depends >-----

#define Util StringHelper

void Convert::getFuncClass(std::vector<std::string>& files,
	std::vector<std::vector<std::vector<int>>>& funcPos, std::vector<std::vector<std::vector<int>>>& classPos)
{
	for (int i = 0; i < files.size(); ++i)
	{
		std::string fileSpec = FileSystem::Path::getFullFileSpec(files[i]);
		std::string msg = "Processing file " + fileSpec;
		Util::title(msg);

		ConfigParseForCodeAnal configure;
		Parser* pParser = configure.Build();
		try
		{
			if (pParser)
			{
				if (!configure.Attach(fileSpec))
				{
					std::string name = files[i];
					std::cout << "\n  could not open file " << name << std::endl;
					continue;
				}
			}
			else
			{
				std::cout << "\n\n  Parser not built\n\n";
				return;
			}
			// now that parser is built, use it

			while (pParser->next())
				pParser->parse();
			std::cout << "\n";

			// show AST
			Repository* pRepo = Repository::getInstance();
			ASTNode* pGlobalScope = pRepo->getGlobalScope();
			TreeWalk(pGlobalScope, funcPos[i], classPos[i]);
			//putline();
		}
		catch (std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
			std::cout << "\n  exception thrown at line " << __LINE__;
		}
	}
}

//----< convert cpp/h files to html >------------------------------------------
//convertToHtml: accept filenames outputed by DirExplorer to convert those files to html files,
//			 then store them in a folder named "ConvertedPages"

void Convert::convertToHtml(std::vector<std::string>& files, std::map<std::string, std::vector<std::string>>& dependencies,
	std::vector<std::vector<std::vector<int>>>& funcPos, std::vector < std::vector<std::vector<int>>>& classPos) {
	//Starting processing
	for (int i = 0; i < files.size(); i++) {
		std::string input = FileSystem::Path::getFullFileSpec(files[i]);
		std::vector<std::vector<int>> funcP = funcPos[i];
		std::vector<std::vector<int>> classP = classPos[i];
		std::vector<std::string > dependency = dependencies[files[i]];
		std::string filename = FileSystem::Path::getName(files[i]);
		std::string outputPath = "../ConvertedPages/" + filename + ".html";
		std::string inputPath = FileSystem::Path::getFullFileSpec(files[i]);
		std::ofstream fout(outputPath);
		std::fstream iout(inputPath);
		std::fstream preOut("../sample.cpp.html");

		//Fail to open ifstream or ofstream
		if (!fout || !iout || !preOut)
		{
			std::cout << "\nFail to convert!" << std::endl;
			return;
		}
		else {
			char ch[256];
			while (!preOut.eof()) {
				preOut.getline(ch, sizeof(ch));
				if (ch[0] == '<' && ch[1] == 'h' && ch[2] == '3') {
					fout << "<h3>" << filename << "</h3>" << std::endl;
					continue;
				}
				fout << ch << std::endl;
				if (ch[0] == '<' && ch[1] == 'p' && ch[2] == 'r' && ch[3] == 'e')
					break;
			}
			fout << "<pre>" << std::endl;
			for (auto depend : dependency) {
				std::string name = FileSystem::Path::getName(depend);
				name.pop_back();
				if (name[0] == '\"')
					name.erase(0, 1);
				fout << "<a href=\"../ConvertedPages/" + name + ".html\">" + FileSystem::Path::getName(depend) + "</a>" << std::endl;
			}
			int rowCount = 1;
			int func_beginCount = 0, func_endCount = 0, class_beginCount = 0, class_endCount = 0;
			int isDoubleComment = 0;
			/*int isSingleComment = 0;*/
			while (!iout.eof()) {
				
				iout.getline(ch, sizeof(ch));

				char newCh[256];
				int i = 0, j = 0, isComment = 0;
				int isFunc = 0, isClass = 0;
				if (func_beginCount < funcP.size()) {
					if (rowCount == funcP[func_beginCount][0]) {
						isFunc = 1;
						func_beginCount++;
					}
				}
				if (class_beginCount < classP.size()) {
					if (rowCount == classP[class_beginCount][0]) {
						isClass = 1;
						class_beginCount++;
					}
				}
				while (ch[i] != '\0') {
					if (ch[i] == '<') {
						newCh[j] = '&';
						newCh[j + 1] = 'l';
						newCh[j + 2] = 't';
						newCh[j + 3] = ';';
						i++;
						j += 4;
					}
					else if (ch[i] == '>') {
						newCh[j] = '&';
						newCh[j + 1] = 'g';
						newCh[j + 2] = 't';
						newCh[j + 3] = ';';
						i++;
						j += 4;
					}
					else
					{
						if (isComment == 0 && ch[i] == '/') {
							if (ch[i + 1] == '/') {
								std::string str = "<span class = \"toggleCommentDisplay\">";
								int k = j;
								for (; k - j < str.length(); k++)
									newCh[k] = str[k - j];
								j = k;
								isComment = 1;
							}
							if (ch[i + 1] == '*') {
								std::string str = "<span class = \"toggleCommentDisplay\">";
								int k = j;
								for (; k - j < str.length(); k++)
									newCh[k] = str[k - j];
								j = k;
								isDoubleComment = 1;
							}
						}
						if (isFunc == 1 && ch[i] == '{') {
							std::string str = "<span class = \"toggleMethodDisplay\">";
							int k = j;
							for (; k - j < str.length(); k++)
								newCh[k] = str[k - j];
							j = k;
							isFunc = 0;
						}
						if (isClass == 1 && ch[i] == '{') {
							std::string str = "<span class = \"toggleClassDisplay\">";
							int k = j;
							for (; k - j < str.length(); k++)
								newCh[k] = str[k - j];
							j = k;
							isClass = 0;
						}
						if (isDoubleComment == 1 && ch[i] == '*' && ch[i + 1] == '/') {
							newCh[j++] = ch[i++];
							newCh[j++] = ch[i++];
							std::string str = "</span>";
							int k = j;
							for (; k - j < str.length(); k++)
								newCh[k] = str[k - j];
							j = k;
							isComment = 0;
							isDoubleComment = 0;
						}
						newCh[j] = ch[i];
						i++;
						j++;
					}
				}
				newCh[j] = '\0';
				fout << newCh;
				if (isComment == 1 && isDoubleComment == 0)
					fout << "</span>";
				if (func_endCount < funcP.size()) {
					if (rowCount == funcP[func_endCount][1]) {
						fout << "</span>";
						func_endCount++;
					}
				}
				if (class_endCount < classP.size()) {
					if (rowCount == classP[class_endCount][1]-1) {
						fout << "</span>";
						class_endCount++;
					}
				}
				fout << std::endl;
				/*if (isSingleComment == 1) {
					fout << "</span>";
					isSingleComment = 0;
				}*/
				rowCount++;
			}
			fout << "</pre>" << std::endl;
			fout << "</body></html>" << std::endl;
		}

		fout.close();
		iout.close();
		preOut.close();
	}
	std::cout << "\n\n  Convert successfully!\n\n";
}

#ifdef TEST_CONVERTER
//----< CONVERT TEST TUB >------------------------------------------
int main() {
	Utilities::Title("Converter: accept filenames to convert those files to html files");
	std::vector<std::string> files = { "../Parser/Parser.cpp", "../Parser/Parser.h" };
	std::map<std::string, std::vector<std::string>> dependencies;
	dependencies["Parser.cpp"] = { "../Utilities/Utilities.h", "../Tokenizer/Toker.h",
								   "../SemiExpression/Semi.h", "Parser.h", "ActionsAndRules.h",
								   "ConfigureParser.h", "../FileSystem/FileSystem.h" };
	dependencies["Parser.h"] = { "../SemiExpression/ITokenCollection.h",
								 "../AbstractSyntaxTree/AbstrSynTree.h" };
	Convert con;
	std::vector<std::vector<std::vector<int>>> funcPos(files.size());
	std::vector<std::vector<std::vector<int>>> classPos(files.size());
	std::cout << "\n\n  1. getFuncClass: get links to all the files in the directory tree, on which it depends" << std::endl;
	con.getFuncClass(files, funcPos, classPos);
	std::cout << "\n\n  2. convertToHtml: convertToHtml: convert cpp/h files to html" << std::endl;
	con.convertToHtml(files, dependencies, funcPos, classPos);

	return 0;
}
#endif