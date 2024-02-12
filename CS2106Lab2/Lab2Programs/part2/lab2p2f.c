#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {

    printf("Be patient, the program will take around 7 seconds to run.\n");
    printf("At the end you can do \"cat results.out\" to see the result.\n");

    // set up pipe
    int p[2];
    // this creates a pipe. p[0] is the reading end,
    // p[1] is the writing end.

    // check for errors in POSIX call
    if (pipe(p) < 0) {
        perror("lab2p2f: ");
    }

    // send message from slow to talk
    if (fork() != 0) {
        // close the reading end of the pipe
        close(p[0]);
        // redirect the standard output of the process to the writing end of the pipe
        dup2(p[1], STDOUT_FILENO);
        // close writing end of pipe
        close(p[1]);
        // execute slow
        char *args[] = {"./slow", "5", NULL};
        execvp(args[0], args);
    } else {
        // close the writing end of the pipe
        close(p[1]);
        // redirect the standard input of the process to the reading end of the pipe
        dup2(p[0], STDIN_FILENO);
        // close the reading end of the pipe
        close(p[0]);
        // open results.out to write the standard output of the process into
        int fp_out = open("./results.out", O_CREAT | O_WRONLY);
        // redirect the standard output of the process to results.out
        dup2(fp_out, STDOUT_FILENO);
        // close the file
        close(fp_out);
        // execute talk
        execlp("./talk", "talk", (char *)0);
    }
    return 0;
}

