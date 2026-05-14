#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("fork failed\n");
        exit(1);

    } else if (pid == 0) {
        printf("Child process (PID: %d) executing 'ls'...\n", getpid());
        execlp("ls", "ls", NULL);

        printf("exec failed\n");
        exit(1);

    } else {
        printf("Parent process (PID: %d) waiting for child (PID: %d)...\n", getpid(), pid);
        wait(NULL);
        printf("Child process has finished. Parent is done.\n");
    }

    exit(0);
}
