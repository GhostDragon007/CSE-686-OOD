/////////////////////////////////////////////////////////////////////////////
// OODProj1.cpp - Program execution begins and ends there                  //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyright @Junhao Shen, 2019                                            //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2019                             //
// Platform:    Dell Latitude , Core i7, Windows 10                        //
// Application: OODProj1.cpp, 2019                                          //
// Author:      Junhao Shen                                                //
//              (315)480-4274, jshen18@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////

#include "pch.h"
using namespace FileSystem;

//Entrance of the program
int main(int argc, char *argv[])
{
	std::cout << "/////////////////////////////////////////////////////////////////////////////\n"
		<< "// CSE687 Project #1 - Source Code Publisher                               //\n"
		<< "// ver 1.0                                                                 //\n"
		<< "// ----------------------------------------------------------------------- //\n"
		<< "// copyright @Junhao Shen, 2019                                            //\n"
		<< "// All rights granted provided that this notice is retained                //\n"
		<< "// ----------------------------------------------------------------------- //\n"
		<< "// Language:    Visual C++, Visual Studio 2017                             //\n"
		<< "// Platform:    Dell Latitude , Core i7, Windows 10                        //\n"
		<< "// Application: Project #1, 2019                                           //\n"
		<< "// Author:      Junhao Shen                                                //\n"
		<< "//              (315)480-4274, jshen18@syr.edu                             //\n"
		<< "/////////////////////////////////////////////////////////////////////////////\n\n";

	std::cout << "Press Enter to continue";
	getchar();
	std::cout << "\n----< 1. Starting DirExplorer >------------------------------------------\n" << std::endl;

	// Initialize a new object DirExplorerN dir, then execute doDirExplore
	// doDirExplorer: accept command parameters to find files fullpathfind files fullpath
	DirExplorerN dir;
	std::vector<std::vector<std::string>> res = dir.doDirExplore(argc, argv);
	std::cout << "\n\n\n----< Ending DirExplorer >------------------------------------------\n\n"
		<< "Press Enter to continue";
	getchar();
	if (res[0].empty())	return 0;
	std::cout << "\n\n\n\n\n\n\n----< 2. Starting Converter >------------------------------------------\n" << std::endl;
	
	// Initialize a new object Convert con, then execute doConvert.
	// doConvert: accept filenames outputed by DirExplorer to convert those files to html files,
    //            then store them in a folder named "ConvertedPages"
	Convert con;
	con.doConvert(res);
	std::cout << "\n\n----< Ending Converter >------------------------------------------\n\n"
		<< "Press Enter to continue";
	getchar();
	std::cout << "\n\n\n\n\n\n\n----< 3. Starting Display >------------------------------------------\n" << std::endl;

	// Initialize a new object Process process, then execute doDisplay.
	// doDisplay: Demonstrating code pop-up from converted html files in Chrome
	Process process;
	//argv[6] is the parameter where user's explorer is located
	std::string appPath = argv[6];
	process.doDisplay(res, appPath);
	std::cout << "\n\n\n----< Ending Display >------------------------------------------\n\n";
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
