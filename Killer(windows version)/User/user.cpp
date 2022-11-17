#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <vector>
#include<string>


int main() {

    DWORD dwPID = 18564; // checking just on tg
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,TRUE,dwPID);
    char szHANDLE[100];
    sprintf(szHANDLE,"%d",hProcess);
    SetEnvironmentVariable("PROC_TO_KILL", szHANDLE);

    TCHAR szInput[1000];
    std::string forCMD = "--name Telegram.exe --name clion64.exe";
    lstrcpyA(szInput, forCMD.c_str());

    STARTUPINFO si = {sizeof(si)};
    SECURITY_ATTRIBUTES saProcess,
            saThread;
    PROCESS_INFORMATION piProcess;

    saProcess.nLength = sizeof(saProcess);
    saProcess.lpSecurityDescriptor = NULL;
    saProcess.bInheritHandle = FALSE;

    saThread.nLength = sizeof(saThread);
    saThread.lpSecurityDescriptor = NULL;
    saThread.bInheritHandle = FALSE;

    if(CreateProcess(R"(D:\BSU\OpSys\killer\cmake-build-debug\killer.exe)",
                     szInput,&saProcess, &saThread,
                     FALSE,0,NULL,NULL, &si, &piProcess)){
        WaitForSingleObject(piProcess.hProcess, INFINITE);
        CloseHandle(piProcess.hThread);
        CloseHandle(piProcess.hProcess);
    }
    SetEnvironmentVariable("PROC_TO_KILL", NULL);
}
