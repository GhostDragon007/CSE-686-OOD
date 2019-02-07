#pragma once
///////////////////////////////////////////////////////////////////////
// Process.h - class used to start process                           //
// ver 1.0                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018         //
// Modified by Junhao Shen, Spring 2019                              //
///////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package provides a class, Process, used to start named processes.
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
*  Process.h, Process.cpp
*
*  Maintenance History:
*  --------------------
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
#include "../DirExplorer-Naive/FileSystem.h"
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
  void doDisplay(std::vector<std::vector<std::string>> input, std::string explorerPath);
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


