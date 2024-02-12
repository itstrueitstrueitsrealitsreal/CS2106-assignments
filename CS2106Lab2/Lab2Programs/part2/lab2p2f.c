#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {

    printf("Be patient, the program will take around 7 seconds to run.\n");
    printf("At the end you can do \"cat results.out\" to see the result.\n");

    //
    // Add code here to pipe from ./slow 5 to ./talk and redirect
    // output of ./talk to results.out
    // I.e. your program should do the equivalent of ./slow 5 | talk > results.out
    // WITHOUT using | and > from the shell.
    //

    // set up pipe
    int p[2];
    // This creates a pipe. p[0] is the reading end,
    // p[1] is the writing end.

    if (pipe(p) < 0) {
        perror("lab2p2f: ");
    }

    // Send message from slow to talk
    if (fork() != 0) {
        close(p[0]);
        dup2(p[1], STDOUT_FILENO);
        close(p[1]);
        char *args[] = {"./slow", "5", NULL};
        execvp(args[0], args);
    } else {
        close(p[1]);
        int fp_out = open("./results.out", O_CREAT | O_WRONLY);
        dup2(fp_out, STDOUT_FILENO);
        close(fp_out);
        close(p[0]);
        execlp("./talk", "./talk", NULL);
    }

    return 0;
}

