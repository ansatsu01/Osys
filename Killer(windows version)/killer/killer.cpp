#include <iostream>
#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string.h>

void killByID(int ID){
    HANDLE handle = OpenProcess(PROCESS_TERMINATE, false, ID);
    if(handle != nullptr){
        TerminateProcess(handle, 0);
        CloseHandle(handle);
    }
}

void killByName(const char* proc_name){
    HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(entry);
    BOOL res = Process32First(snapShot, &entry);
    while(res){
        if(strcmp(proc_name, entry.szExeFile) == 0){
            HANDLE handle = OpenProcess(PROCESS_TERMINATE, false, entry.th32ProcessID);
            if(handle != nullptr){
                TerminateProcess(handle, 0);
                CloseHandle(handle);
            }
        }
        res = Process32Next(snapShot, &entry);
    }
    CloseHandle(snapShot);
}

int main(int argc, char *argv[]) {
    for(int i =0; i < argc; i++){
        if(strcmp(argv[i], "--id") == 0){
            killByID(std::atoi(argv[i+1]));
        }
        if(strcmp(argv[i], "--name") == 0){
            killByName(argv[i+1]);
        }
    }


}
