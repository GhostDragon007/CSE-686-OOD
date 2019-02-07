/////////////////////////////////////////////////////////////////////////////
// Convert.h - accept filenames outputed by DirExplorer to convert         //
//               those files to html files                                 //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyright @Junhao Shen, 2019                                            //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2019                             //
// Platform:    Dell Latitude , Core i7, Windows 10                        //
// Application: Convert.h, 2019                                            //
// Author:      Junhao Shen                                                //
//              (315)480-4274, jshen18@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "../DirExplorer-Naive/StringUtilities.h"
#include "../DirExplorer-Naive/FileSystem.h"

class Convert
{
public:
	Convert();
	~Convert();
	void doConvert(std::vector<std::vector<std::string>> input);
};

