#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define NUM_CHILDREN 5

int main()
{

    int i;
    int *shm;

    pid_t pid;
    // create Shared Memory Region
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);
    if (shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    // attach the shared memory region to this process
    shm = shmat(shmid, NULL, 0);
    if (shm == (int*) -1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    *shm = 0;
    for (i = 0; i < NUM_CHILDREN; i++)
    {
        pid = fork();
        if (pid == 0)
            break;
    }
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child %d starts\n", i + 1);
        // Simulate some work
        for (int j = 0; j < 5; j++)
        {
            (*shm)++;
            printf("Child %d increment counter %d\n", i + 1, *shm);
            fflush(stdout);
            usleep(250000);
        }
        printf("Child %d finishes with counter %d\n", i + 1, *shm);
        exit(EXIT_SUCCESS);
    }

    // Parent process
    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        wait(NULL);
    }

    // Print the final value of the counter
    printf("Final counter value: %d\n", *shm);
    // Detach the shared memory segment
    if (shmdt(shm) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
