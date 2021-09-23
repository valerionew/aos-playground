#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

/*

This is identical to the pipe, with the difference that
this actually uses a filename that is specified

It won't actually be a file on the disk, and the OS
will handle everything 

*/

int main () {
   
    const char * myfifo = "/tmp/myfifo";
    int fd = open(myfifo, O_RDONLY); // open the pipe in read mode
    if (fd <= 0) {
        printf("Cannot open fifo\n"); // pians
        return 1;
    }

    float data;
    int nb = read(fd, &data, sizeof(data));
    if (nb == 0) {
        printf("Read error\n");
        return 1;
    }
    
    printf("Read: %f\n", data);

    close(fd);
    return 0;
}
