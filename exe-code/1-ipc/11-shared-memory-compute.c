#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <unistd.h>

struct fibo_status {
    char ready;
    char done;
	int a;
	int b;
};

int main() {

    int fd = shm_open("/fibo_shm", O_RDWR, 0666);
    if (fd < 0) {
        printf("SHM Error: %s", strerror(errno));
        return 1;
    }

    void *ptr_shm = mmap(NULL, sizeof(struct fibo_status), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr_shm == MAP_FAILED) {
        printf("MAP FAILED: %s\n", strerror(errno));
        return 1;
    }

    struct fibo_status * p = (struct fibo_status *)ptr_shm;

    int c=0;
    while(p->done == 0) {
        while(p->ready);
        c = p->a + p->b;
        p->a = p->b;
        p->b = c;
        p->ready = 1;
    }
    
    munmap(ptr_shm, sizeof(struct fibo_status)); // free the space
    shm_unlink("/fibo_shm");
    
    return 0;
}
