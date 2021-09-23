#include <errno.h>
#include <semaphore.h> // requires gcc -pthread
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <unistd.h>

/*
Semaphores are like semaphores for threads, but now are for processes

There are semaphores that are limited to the 0/1 range, (go/nogo)? and arecalled binary

Semaphores can be named or unnamed. For an unnamed semaphore it is required to have
a parent-child relationship between processes. 

The status of a semamphore can be checked with sem_wait, sem_trywait (non-blocking)
or sem_timedwait


*/

struct fibo_status {    
    char done;
	int a;
	int b;
};

int main() {

    int fd = shm_open("/fibo_shm", O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        printf("SHM Error: %s", strerror(errno));
        return 1;
    }
    
    ftruncate(fd, sizeof(struct fibo_status));

    void *ptr_shm = mmap(NULL, sizeof(struct fibo_status), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr_shm == MAP_FAILED) {
        printf("MAP FAILED: %s\n", strerror(errno));
        return 1;
    }

    sem_t *my_sem_1 = sem_open("/fibo_sem_1", O_CREAT, 0666, 0);
    sem_t *my_sem_2 = sem_open("/fibo_sem_2", O_CREAT, 0666, 1);

    struct fibo_status * p = (struct fibo_status *)ptr_shm;
    p->done = 0;
    p->a = 0;
    p->b = 1;

    printf("0\n1\n");

    int c=0;
    while(c < 1000) {
        sem_wait(my_sem_1);
        c = p->a + p->b;
        printf("%d\n", c);
        sem_post(my_sem_2);
    }
    
    p->done = 1;
    sem_post(my_sem_2);
    sem_close(my_sem_1);
    sem_close(my_sem_2);
    munmap(ptr_shm, sizeof(struct fibo_status));

    return 0;
}
