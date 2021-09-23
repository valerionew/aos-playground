#include <fcntl.h> 
#include <math.h> // needs to be linked: gcc -lm ...
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
/*

Pipes are used to communicate between processes. 


*/


int main() {

    float number;
    printf("Please insert a number: ");
    scanf("%f", &number);
    
    int fd[2]; // fd[0] is the read end, fd[1] is the write end
    pipe(fd); // send the pointer to the file descriptor
    
    int id = fork();
    if (id == 0) {
        // Child
        close(fd[0]); // we close the non-interesting end of the pipe (the child will only write in the pipe)
                // QUESTION
                // why do we have to close it? do we HAVE TO close it? -> YES
                // can the same pipe work both ways?  -> NO
                // is this allowed? is it a bad practice? -> NOT ALLOWED

        float result = sqrt(number);
        write(fd[1], &result, sizeof(result));
        close(fd[1]); // we finished here, close the pipe.  
        
    } else {
        // Parent
        close(fd[1]);  // we close the non-interesting end of the pipe

            // QUESTION
                // How does the synchronization between the two process work?
                // what if a process has already terminated (and written in the pipe)
                // and the other didn't close the unused end yet?
        float result = sqrt(number);
        float result_from_child;
        read(fd[0], &result_from_child, sizeof(result_from_child));
        close(fd[0]);
        wait(NULL); // we have to wait for the children, as to not create a zombie process
        
        if (result_from_child == result) {
            printf("sqrt(%f)=%f\n", number, result);
        } else {
            printf("Incorrect computation? %f != %f\n", result_from_child, result);        
        }
        
    }

    return 0;
}
