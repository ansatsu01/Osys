#include <sys/wait.h>
#include <unistd.h>
#include <vector>


void createProcess(int in, int out, const char* path){
    if (fork() == 0) {
        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);//1
        close(in);
        close(out);
        execl(path, nullptr);
        exit(0);
    }
}


int main()
{
    const char *pathM = "../../M/cmake-build-debug/M";
    const char *pathA = "../../A/cmake-build-debug/A";
    const char *pathP = "../../P/cmake-build-debug/P";
    const char *pathS = "../../S/cmake-build-debug/S";

    int pipefdMA[2];
    int pipefdAP[2];
    int pipefdPS[2];
    int status;

    pipe(pipefdMA);
    pipe(pipefdAP);
    pipe(pipefdPS);

    int in = dup(STDIN_FILENO);
    int out = dup(STDOUT_FILENO);
    close(STDIN_FILENO);

    createProcess(in, pipefdMA[1], pathM);
    createProcess(pipefdMA[0], pipefdAP[1], pathA);
    createProcess(pipefdAP[0], pipefdPS[1], pathP);
    createProcess(pipefdPS[0], out, pathS);

    for (int i = 0; i < 4; ++i) {
        wait(&status);
    }
}
