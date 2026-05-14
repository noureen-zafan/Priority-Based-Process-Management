#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int fd[2];
    int pid;

    char message[] = "Hello from child process!";
    char buffer[100];

    // 1. Create pipe
    if (pipe(fd) < 0) {
        printf("Pipe failed\n");
        exit(1);
    }

    // 2. Fork process
    pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    // 3. Child process
    if (pid == 0) {
        close(fd[0]); // close read end

        int n = write(fd[1], message, strlen(message) + 1);
        if (n < 0) {
            printf("Write failed\n");
            exit(1);
        }

        close(fd[1]); // close write end
        exit(0);
    }

    // 4. Parent process
    else {
        close(fd[1]); // close write end

        int m = read(fd[0], buffer, sizeof(buffer));
        if (m < 0) {
            printf("Read failed\n");
            exit(1);
        }

        printf("Parent received: %s\n", buffer);

        close(fd[0]); // close read end
        wait(0); // wait for child
    }

    exit(0);
}
