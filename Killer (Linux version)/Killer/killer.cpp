#include <iostream>
#include <signal.h>
#include <string.h>

void killByID(int id){
    pid_t pid = id;
    kill(id, SIGTERM);
}

void killByName(char* name){
    char buf[512];
    char command[50];
    sprintf(command, "pidof -s %s", name);
    FILE *cmd_pipe = popen(command, "r");

    fgets(buf, 512, cmd_pipe);
    pid_t pid = strtoul(buf, NULL, 10);

    pclose( cmd_pipe );
    killByID(pid);
}


int main(int argc, char* argv[]) {
    char* env_var = getenv("PROC_TO_KILL");
    killByName(env_var);

    for(int i = 0; i < argc; i++){
        std::string str = argv[i];
        if(strcmp(argv[i], "--id") == 0){
            killByID(std::atoi(argv[i+1]));
        }
        if(strcmp(argv[i], "--name") == 0){
            killByName(argv[i+1]);
        }
    }
}
