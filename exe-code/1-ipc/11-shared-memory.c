#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h> // gcc -lrt
#include <sys/types.h>
#include <unistd.h>

/*
Shared memory is often used

a memory segment is shared between two processes
When this is set up, the OS is no more involved in the communication (non syscall etc)



*/

struct fibo_status {
    char ready;
    char done;
	int a;
	int b;
};

int main() {

    int fd = shm_open("/fibo_shm", O_RDWR | O_CREAT, 0666); // the file descriptor is used differently this time.
    if (fd < 0) {
        printf("SHM Error: %s", strerror(errno));
        return 1;
    }
    
    ftruncate(fd, sizeof(struct fibo_status)); // define the shared memory size

    void *ptr_shm = mmap(NULL, sizeof(struct fibo_status), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr_shm == MAP_FAILED) {
        printf("MAP FAILED: %s\n", strerror(errno));
        return 1;
    }
    
    // if everthing was successful, now we have a pointer to shared memory that is void type
    struct fibo_status * p = (struct fibo_status *)ptr_shm; // we cast the type here

    p->done = 0;
    p->ready = 0;
    p->a = 0;
    p->b = 1;

    printf("0\n1\n");

    int c=0;
    while(c < 1000) {
        while(!p->ready);
        c = p->a + p->b;
        printf("%d\n", c);
        p->ready = 0;
    }

    p->ready = 0;
    p->done = 1;
    
    munmap(ptr_shm, sizeof(struct fibo_status)); // free the space
    
    return 0;
}
