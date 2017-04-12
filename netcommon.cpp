#include <stdio.h>
#include <unistd.h>


int Read(int fd, char *buf, int len) {

    int n;
    if ((n = ::read(fd, buf, len)) == -1) {
        perror("while reading");
    }

    return n;
}
