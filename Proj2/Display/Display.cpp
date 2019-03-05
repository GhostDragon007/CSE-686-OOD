/////////////////////////////////////////////////////////////////////////////
// Display.cpp - display converted html pages in user's browser            //
// ver 1.1                                                                 //
// Language:    Visual C++, Visual Studio 2019                             //
// Platform:    Dell Latitude , Core i7, Windows 10                        //
// Application: CSE687 - OOD Project #2                                    //
// Author:      Junhao Shen                                                //
//              (315)480-4274, jshen18@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////

#include "Display.h"
#include "../FileSystem/FileSystem.h"

CBP Process::cbp_ = []() { std::cout << "\n  --- child process exited ---"; };

//----< Process constructor >------------------------------------------
/*
* - This eventually will have more functionality
*/
inline Process::Process()
{
	GetStartupInfo(&startInfo_);
	startInfo_.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	startInfo_.dwX = 200;
	startInfo_.dwY = 250;
	startInfo_.dwYSize = 300;
}

inline void Process::application(const std::string& appName)
{
	appName_ = sToW(appName);
}
//----< define commandline passed to new application >-----------------

inline void Process::commandLine(const std::string& cmdLine)
{
	commandLine_ = sToW(cmdLine);
}
//----< define title bar for console window >--------------------------
/*
* - applications like Notepad overwrite this string
*/
inline void Process::title(const std::string& title)
{
	title_ = sToW(title);
	startInfo_.lpTitle = const_cast<LPWSTR>(title_.c_str());
}
//----< start new child process >--------------------------------------

inline bool Process::create(const std::string& appName)
{
	std::wstring app;
	if (appName.size() == 0)
		app = appName_;
	else
	{
		app = sToW(appName);
	}
	LPCTSTR applic = app.c_str();
	LPTSTR cmdLine = const_cast<LPTSTR>(commandLine_.c_str());
	LPSECURITY_ATTRIBUTES prosec = nullptr;
	LPSECURITY_ATTRIBUTES thrdsec = nullptr;
	BOOL inheritHandles = false;
	DWORD createFlags = CREATE_NEW_CONSOLE;  // or CREATE_NO_WINDOW
	LPVOID environment = nullptr;
	LPCTSTR currentPath = nullptr;
	LPSTARTUPINFO pStartInfo = &startInfo_;
	LPPROCESS_INFORMATION pPrInfo = &procInfo_;

	BOOL OK =
		CreateProcess(
			applic, cmdLine, prosec, thrdsec, inheritHandles,
			createFlags, environment, currentPath, pStartInfo, pPrInfo
		);
	return OK;
}

///////////////////////////////////////////////////////////////////////
// child process exit callback processing

//----< provide new callable object for callback to invoke >-----------

void Process::setCallBackProcessing(CBP cbp)
{
	cbp_ = cbp;
}
//----< function called when child process exists >--------------------

void Process::callback()
{
	cbp_();
}

//----< register callback with Windows API >---------------------------

void Process::registerCallback()
{
	HANDLE hNewHandle;
	HANDLE hProcHandle = procInfo_.hProcess;
	RegisterWaitForSingleObject(
		&hNewHandle, hProcHandle, WaitOrTimerCallback,
		NULL, INFINITE, WT_EXECUTEONLYONCE
	);
}

HANDLE Process::getProcessHandle()
{
	return procInfo_.hProcess;
}

//----< helper function to convert strings >---------------------------

std::string wToS(const std::wstring& ws)
{
	std::string conv;
	for (auto ch : ws)
	{
		conv.push_back(static_cast<char>(ch));
	}
	return conv;
}

//----< helper function to convert strings >---------------------------

std::wstring sToW(const std::string& s)
{
	std::wstring conv;
	for (auto ch : s)
	{
		conv.push_back(static_cast<wchar_t>(ch));
	}
	return conv;
}

//----< Windows API declared function type for callbacks >-------------

void CALLBACK WaitOrTimerCallback(_In_ PVOID lpParameter, _In_ BOOLEAN TimerOrWaitFired)
{
	Process p;
	p.callback();
	return;
}


//----< pop_out html files in Chrome >---------------------------------

void Process::pop_out(std::vector<std::string> files, std::string explorerPath)
{
	Process p;
	p.title("test application");
	std::string appPath = explorerPath;
	//std::string appPath = "C:/Users/47221/AppData/Local/Google/Chrome/Application/chrome.exe";  // path to application to start
	p.application(appPath);

	std::cout << "\n  You need to kill each window (upper right button) to continue.\n\n";
	std::cout << "  MAKE SURE YOU HAVE CLOSED YOUR BROWSER!!!\n";
	std::cout << "\n  Press key to start";
	_getche();

	for (int i = 0; i < files.size(); ++i)
	{
		std::string filePath = "../ConvertedPages/" + FileSystem::Path::getName(files[i]) + ".html";
		std::string filename = FileSystem::Path::getFullFileSpec(filePath);
		std::string cmdLine = "/A \"" + filename + "\"";  // asking chrome to display Process.h
		p.commandLine(cmdLine);
		std::cout << "\n  starting process: \"" << appPath << "\"";
		std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
		p.create();
		CBP callback = []() { std::cout << "\n  --- child process exited with this message ---"; };
		p.setCallBackProcessing(callback);
		p.registerCallback();

		WaitForSingleObject(p.getProcessHandle(), INFINITE);  // wait for created process to terminate
	}

	std::cout << "\n  after OnExit";
	std::cout.flush();
	char ch;
	std::cin.read(&ch, 1);

}

//----< DISPLAY TEST STUB >--------------------------------------------

#ifdef TEST_DISPLAY
int main() {
	std::cout << "\n  Display: Demonstrating code pop-up in Chrome";
	std::cout << "\n ======================================";
	std::vector<std::string> files = { "../Parser/Parser.cpp", "../Parser/Parser.h"};
	std::string appPath = "C:/Users/47221/AppData/Local/Google/Chrome/Application/chrome.exe";
	Process pro;
	pro.pop_out(files, appPath);

	return 0;
}
#endif
