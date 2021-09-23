#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
/*

This is identical to the pipe, with the difference that
this actually uses a filename that is specified

It won't actually be a file on the disk, and the OS
will handle everything 




PERMISSIONS IN LINUX:
Every file can have three permissionis: (r)ead, (w)rite, e(x)ecute

they correspond to a power of two
r -> 4
w -> 2
x -> 1

There are 3 entities that can have permissions:
Owner:  who created the file
Group:  the group of many users
Others: anyone

The permission is usually written in an octal representation
and it's usually prepend by '0'.
For example 0755 means: owner rwx, group r-x, others r-x.
The x for the directories means beeing able to go
through the directories
*/

int main () {

    const char * myfifo = "/tmp/myfifo";
    if (mkfifo(myfifo, 0666) != 0) { // mkfifo creates the pipe (fifo) assignign permissions - triplo sei su ogni cosa?
        printf("Cannot create fifo.\n"); // pians
        return 1;
    }
    
    int fd = open(myfifo, O_WRONLY); // open in write mode
    if (fd <= 0) {
        printf("Cannot open fifo\n"); // pians
        unlink(myfifo); // ??
        return 1;
    }

    float data = 10;
    int nb = write(fd, &data, sizeof(data));
    if (nb == 0) {
        printf("Write error\n");
    }    
    
    printf("OK\n");
    
    close(fd);
    unlink(myfifo);
    return 0;
}
