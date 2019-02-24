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

void Convert::doConvert(std::vector<std::vector<std::string>> input) {
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

		//Fail to open ifstream or ofstream
		if (!fout || !iout)
		{
			std::cout << "\nFail to convert!" << std::endl;
			return;
		}
		else {
			fout << "<!Doctype html>" << std::endl;
			fout << "<html>" << std::endl;
			fout << "<head>" << std::endl;
			fout << "<style>" << std::endl;
			fout << "body{" << std::endl;
			fout << "padding: 15px 40px;" << std::endl;
			fout << "font - family: Consolas;" << std::endl;
			fout << "font - size: 1.25em;" << std::endl;
			fout << "font - weight: normal;" << std::endl;
			fout << "}" << std::endl;
			fout << "</style>" << std::endl;
			fout << "</head>" << std::endl;
			fout << "<body>" << std::endl;
			fout << "<h3>" << filename << "</h3>" << std::endl;
			fout << "<pre>" << std::endl;
			char ch[256];
			while (!iout.eof()) {
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
			}
			fout << "</pre>" << std::endl;
			fout << "</body></html>" << std::endl;
		}

		fout.close();
		iout.close();
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