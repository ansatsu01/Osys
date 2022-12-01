#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>

int main()
{
	const wchar_t* pathMProcess = L"../x64/Debug/M.exe";
	const wchar_t* pathAProcess = L"../x64/Debug/A.exe";
	const wchar_t* pathPProcess = L"../x64/Debug/P.exe";
	const wchar_t* pathSProcess = L"../x64/Debug/S.exe";

	std::vector<HANDLE> hPipes;
	auto closePipes = [&hPipes]() {
		std::for_each(hPipes.begin(), hPipes.end(), CloseHandle);
	};

	SECURITY_ATTRIBUTES saPipe = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

	HANDLE readPipeMA, writePipeMA;
	bool pipeMA = CreatePipe(&readPipeMA, &writePipeMA, &saPipe, 0);
	hPipes.push_back(readPipeMA);
	hPipes.push_back(writePipeMA);

	HANDLE readPipeAP, writePipeAP;
	bool pipeAP = CreatePipe(&readPipeAP, &writePipeAP, &saPipe, 0);
	hPipes.push_back(readPipeAP);
	hPipes.push_back(writePipeAP);

	HANDLE readPipePS, writePipePS;
	bool pipePS = CreatePipe(&readPipePS, &writePipePS, &saPipe, 0);
	hPipes.push_back(readPipePS);
	hPipes.push_back(writePipePS);

	STARTUPINFO startInfoProcessM, startInfoProcessA, startInfoProcessP, startInfoProcessS;

	GetStartupInfo(&startInfoProcessM);
	startInfoProcessM.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	startInfoProcessM.hStdOutput = writePipeMA;
	startInfoProcessM.dwFlags = STARTF_USESTDHANDLES;

	std::vector<PROCESS_INFORMATION> processes;
	auto closeAllProcesses = [&processes]() {
		std::for_each(processes.begin(), processes.end(), [](const PROCESS_INFORMATION& process_Info) {
			TerminateProcess(process_Info.hProcess, 1);
			CloseHandle(process_Info.hThread);
			CloseHandle(process_Info.hProcess);
			});
	};

	PROCESS_INFORMATION processM_Info;
	if (!CreateProcess(pathMProcess, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoProcessM, &processM_Info)) {
		return 1;
	}
	processes.push_back(processM_Info);

	GetStartupInfo(&startInfoProcessA);
	startInfoProcessA.hStdInput = readPipeMA;
	startInfoProcessA.hStdOutput = writePipeAP;
	startInfoProcessA.dwFlags = STARTF_USESTDHANDLES;

	PROCESS_INFORMATION processA_Info;
	if (!CreateProcess(pathAProcess, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoProcessA, &processA_Info)) {
		closeAllProcesses();
		return 1;
	}
	processes.push_back(processA_Info);

	GetStartupInfo(&startInfoProcessP);
	startInfoProcessP.hStdInput = readPipeAP;
	startInfoProcessP.hStdOutput = writePipePS;
	startInfoProcessP.dwFlags = STARTF_USESTDHANDLES;

	PROCESS_INFORMATION processP_Info;
	if (!CreateProcess(pathPProcess, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoProcessP, &processP_Info)) {
		closeAllProcesses();
		return 1;
	}
	processes.push_back(processP_Info);

	GetStartupInfo(&startInfoProcessS);
	startInfoProcessS.hStdInput = readPipePS;
	startInfoProcessS.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	startInfoProcessS.dwFlags = STARTF_USESTDHANDLES;

	PROCESS_INFORMATION processS_Info;
	if (!CreateProcess(pathSProcess, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoProcessS, &processS_Info)) {
		closeAllProcesses();
		return 1;
	}
	processes.push_back(processS_Info);

	std::for_each(processes.begin(), processes.end(), [](const PROCESS_INFORMATION& process_Info) {
		WaitForSingleObject(process_Info.hProcess, INFINITY);
		CloseHandle(process_Info.hThread);
		CloseHandle(process_Info.hProcess);
		});

	closePipes();
}
