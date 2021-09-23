#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
One can "mask" signals to ignore them
There are two signals that can't be ignored: SIGKILL and SIGSTOP

For example one can send the interrupt signal to stop the program with SIGINT

The signals are handled as a "flag", so nobody counts the number of same signals 
received by a process if the process does not act on it.

For example masking signals prevents signals from reaching the process
but only AS LONG as they stay blocked. As soon as one calls UNBLOCK, the signal 
that was waiting is received

*/
void my_handler(int) {
    printf("Handling the signal...\n");
}

int main() {

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    
    sa.sa_handler = &my_handler;  // populates the struct
    sigaction(SIGINT, &sa, NULL); // assigns the handler for the interrupt signal

    sigset_t my_sig_set;                        //2nd part
    sigemptyset(&my_sig_set);                   //2nd part
    sigaddset(&my_sig_set, SIGINT);             //2nd part
    sigprocmask(SIG_BLOCK, &my_sig_set, NULL);  //2nd part

    for(int i=0; i<5; i++) {
        printf("Sleeping...\n");
        sleep(1);
    }

    sigprocmask(SIG_UNBLOCK, &my_sig_set, NULL);    //2nd part

	return 0;
}
