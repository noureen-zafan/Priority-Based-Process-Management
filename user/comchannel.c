#include "kernel/types.h"
#include "user/user.h"

int main() {
    int fds[2];  // Pipe file descriptors
    char buf[100];  // Buffer to hold data read from pipe
    int n;

    // Create the pipe
    if (pipe(fds) < 0) {
        fprintf(2, "pipe failed\n");
        exit(1);
    }

    // Fork a new process
    int pid = fork();
    if (pid < 0) {
        fprintf(2, "fork failed\n");
        exit(1);
    }

    if (pid > 0) {
        // Parent process: Write to the pipe
        write(fds[1], "Hello from parent\n", 18);  // Write some data to the pipe
        wait(0);  // Wait for the child to finish
    } else {
        // Child process: Read from the pipe
        n = read(fds[0], buf, sizeof(buf));  // Read data from the pipe
        if (n > 0) {
            write(1, buf, n);  // Display the data on the terminal
        }
    }

    exit(0);  // Exit the program
}
