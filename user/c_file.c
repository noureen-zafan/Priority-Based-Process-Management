#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(){
    int fd = open("out", O_WRONLY | O_CREATE | O_TRUNC);
    char *msg = "this is noureen\n";
    printf("open returned fd %d\n", fd);
    write(fd, msg, strlen(msg));
    close(fd);
    exit(0);
}
