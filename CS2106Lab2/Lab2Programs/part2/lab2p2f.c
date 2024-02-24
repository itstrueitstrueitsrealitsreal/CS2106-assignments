#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    //
    // Add code here to pipe from ./slow 5 to ./talk and redirect
    // output of ./talk to results.out
    // I.e. your program should do the equivalent of ./slow 5 | talk > results.out
    // WITHOUT using | and > from the shell.
    //
    int p[2];

    // This creates a pipe. p[0] is the reading end,
    // p[1] is the writing end.

    if(pipe(p) < 0) 
        perror("lab2p2e: ");

    // We will send a message from father to child
    if(fork() == 0) {
        // Child Process
        // Run Slow in this Process
        close(p[0]); // The the end we are not using.
        
        dup2(p[1], STDOUT_FILENO);
        close(p[1]);
        execlp("./slow", "slow", "5", NULL);
        // Redirect output of ./talk to p[1]
    }
    else
    {
        wait(NULL);
        //Parent Process
        close(p[1]); // Close the writing end
        //Run Talk in this Process
        dup2(p[0], STDIN_FILENO);
        close(p[0]);
        int fp_out = open("./results.out", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        dup2(fp_out, STDOUT_FILENO);
        close(fp_out);
        // Redirect output of ./slow to p[0]
        execlp("./talk", "talk", NULL);
    }
}

