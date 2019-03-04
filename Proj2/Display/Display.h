#pragma once
/////////////////////////////////////////////////////////////////////////////
// Display.h  - display converted html pages in user's browser             //
// ver 1.1                                                                 //
// Language:    Visual C++, Visual Studio 2019                             //
// Platform:    Dell Latitude , Core i7, Windows 10                        //
// Application: CSE687 - OOD Project #2                                    //
// Author:      Junhao Shen                                                //
//              (315)480-4274, jshen18@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package provides a class, Display, used to start named processes.
*  It has a lot of potential, mostly unrealized by this simple beginning.
*
*  Possible future features include:
*  - interprocess communication between parent and child using pipes
*  - handling multiple process, perhaps in a process pool
*  - killing processes
*  - enumerating running processes that match a regular expression
*  - yada, yada, yada
*
*  Required Files:
*  ---------------
*  Display.h, Display.cpp
*  FileSystem.h, FileSystem.cpp
*
*  Maintenance History:
*  --------------------
*  ver 1.1 :  4 Mar 2019
*  - add pop_out method to display a file
*  ver 1.0 : 19 Feb 2018
*  - first release
*/
#include <windows.h>
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <fstream>
#include <conio.h>


using CBP = std::function<void(void)>;

class Process
{
public:
	Process();
	virtual ~Process() {}
	bool create(const std::string& path = "");
	void title(const std::string& title);
	void application(const std::string& app);
	void commandLine(const std::string& cmdLine);
	void registerCallback();
	void setCallBackProcessing(CBP cbp);
	void callback();
	HANDLE getProcessHandle();
	
	void pop_out(std::vector<std::string> input, std::string explorerPath);

private:
	STARTUPINFO startInfo_;
	PROCESS_INFORMATION procInfo_;
	std::wstring title_;
	std::wstring appName_;
	std::wstring commandLine_;
	static CBP cbp_;
};


//----< helper function to convert strings >---------------------------

std::string wToS(const std::wstring& ws);

//----< helper function to convert strings >---------------------------

std::wstring sToW(const std::string& s);

//----< define application new process runs >--------------------------


//----< Windows API declared function type for callbacks >-------------

void CALLBACK WaitOrTimerCallback(_In_ PVOID lpParameter, _In_ BOOLEAN TimerOrWaitFired);


