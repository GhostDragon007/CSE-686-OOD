/////////////////////////////////////////////////////////////////////////////
// Convert.cpp - accept filenames outputed by DirExplorer to convert       //
//               those files to html files                                 //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyright @Junhao Shen, 2019                                            //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2019                             //
// Platform:    Dell Latitude , Core i7, Windows 10                        //
// Application: Convert.cpp, 2019                                          //
// Author:      Junhao Shen                                                //
//              (315)480-4274, jshen18@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////

#include "Convert.h"

Convert::Convert(){}
Convert::~Convert(){}

//----< Do converting >------------------------------------------
//Converter: accept filenames outputed by DirExplorer to convert those files to html files,
//			 then store them in a folder named "ConvertedPages"

void Convert::doConvert(std::vector<std::vector<std::string>> input, std::vector<std::vector<int>> position) {
	Utilities::Title("Converter: accept filenames outputed by DirExplorer to convert those files to html files");
	std::vector<std::string> vec_fileName = input[0];
	std::vector<std::string> vec_fullPath = input[1];
	//Starting processing
	for (int i = 0; i < vec_fileName.size(); i++) {
		std::string filename = "../ConvertedPages/" + vec_fileName[i] + ".html";
		std::string fullPath = vec_fullPath[i];
		std::string fpath = FileSystem::Path::getFullFileSpec(filename);
		filename = vec_fileName[i];
		std::ofstream fout(fpath);
		std::fstream iout(fullPath);
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
				fout << ch << std::endl;
				if (ch[0] == '<' && ch[1] == 'p' && ch[2] == 'r' && ch[3] == 'e')
					break;
			}
			fout << "<pre>" << std::endl;
			int rowCount = 1;
			int beginCount = 0, endCount = 0;
			while (!iout.eof()) {
				if (beginCount < position[0].size()) {
					if (rowCount == position[0][beginCount]) {
						fout << "<span class = \"toggleMethodDisplay\">";
						beginCount++;
					}
				}
				iout.getline(ch, sizeof(ch));
				char newCh[256];
				int i = 0, j = 0;
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
						newCh[j] = ch[i];
						i++;
						j++;
					}
				}
				newCh[j] = '\0';
				fout << newCh << std::endl;
				if (endCount < position[1].size()) {
					if (rowCount == position[1][endCount]) {
						fout << "</span>";
						endCount++;
					}
				}
				rowCount++;
			}
			fout << "</pre>" << std::endl;
			fout << "</body></html>" << std::endl;
		}

		fout.close();
		iout.close();
		preOut.close();
	}
	std::cout << "\n\nConvert successfully!\n\n";
}

#ifdef TEST_CONVERT
//----< CONVERT TEST TUB >------------------------------------------
int main() {
	std::vector<std::vector<std::string>> input;
	std::vector<std::string> fileName;
	fileName.push_back("C:/Users/47221/Desktop/OODProj1/Display/Convert.h");
	fileName.push_back("C:/Users/47221/Desktop/OODProj1/Display/Convert.cpp");
	input.push_back(fileName);
	std::vector<std::string> path;
	path.push_back("Convert.h");
	path.push_back("Convert.cpp");
	input.push_back(path);

	Convert con;
	con.doConvert(input);

	return 0;
}
#endif