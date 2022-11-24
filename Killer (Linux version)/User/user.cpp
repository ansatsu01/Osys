#include <iostream>
#include <unistd.h>
#include <wait.h>

int main() {
    std::string env_name = "PROC_TO_KILL";
    std::string put_env = "Telegram";
    setenv(env_name.c_str(), put_env.c_str(), 0);
    int pid = fork();
    if(pid == 0){
        char* inputKiller[] = {"--id", "3854"};
        execv("/home/victoria/CLionProjects/killer/cmake-build-debug/killer", inputKiller);
        exit(0);
    } else if(pid > 0){
        int status;
        waitpid(pid, &status, 0);
        unsetenv(env_name.c_str());
    }else{
        std::cout << "Error, not forked!\n";
    }

    return 0;
}
