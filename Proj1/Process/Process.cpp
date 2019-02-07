///////////////////////////////////////////////////////////////////////
// Process.cpp - class used to start process                         //
// ver 1.0                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018         //
// Modified by Junhao Shen, Spring 2019                              //
///////////////////////////////////////////////////////////////////////

#include "Process.h"

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

//----< DO DISPLAY >-------------------
//Display: Demonstrating code pop-up from converted html files in Chrome
void Process::doDisplay(std::vector<std::vector<std::string>> input, std::string explorerPath)
{
	std::vector<std::string> vec_fileName = input[0];



	std::cout << "\n  Display: Demonstrating code pop-up in Chrome";
	std::cout << "\n ======================================";


	Process p;
	p.title("test application");
	std::string appPath = explorerPath;
	//std::string appPath = "C:/Users/47221/AppData/Local/Google/Chrome/Application/chrome.exe";  // path to application to start
	p.application(appPath);

	std::cout << "\n  You need to kill each window (upper right button) to continue.\n\n";
	std::cout << "  MAKE SURE YOU HAVE CLOSED YOUR EXPLORER!!!\n";
	std::cout << "\n  Press key to start";
	_getche();

	for (int i = 0; i < vec_fileName.size(); ++i)
	{
		std::string filename = vec_fileName[i];
		std::string realName = "../ConvertedPages/" + filename + ".html";
		filename = FileSystem::Path::getFullFileSpec(realName);
		/*for (int i = 0; i < filename.length(); i++) {
			if (filename[i] == 32) {
				filename[i] = '+';
			}
		}*/
		
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

//----< DISPLAY TEST STUB >-------------------
#ifdef TEST_PROCESS
int main() {
	std::vector<std::vector<std::string>> input;
	std::vector<std::string> fileName;
	fileName.push_back("Convert.cpp");
	input.push_back(fileName);
	std::string appPath = "C:/Users/47221/AppData/Local/Google/Chrome/Application/chrome.exe";
	Process pro;
	pro.doDisplay(input, appPath);

	return 0;
}
#endif
