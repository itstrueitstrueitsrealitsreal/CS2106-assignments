#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#define NUM_CHILDREN 5

int main()
{

    int i;
    int *shm;

    pid_t pid;

    // create Shared Memory Region for counter variable
    int ctrid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);
    if (ctrid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    // attach the shared memory region to this process
    shm = shmat(ctrid, NULL, 0);
    if (shm == (int*) -1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // create Shared Memory Region for semaphores
    int semid = shmget(IPC_PRIVATE, NUM_CHILDREN * sizeof(sem_t), IPC_CREAT | 0600);
    if (semid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    // attach the shared memory region to this process
    sem_t *sems = shmat(semid, NULL, 0);
    if (sems == (sem_t*) -1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // initialise counter to 0
    *shm = 0;
    // Initialize semaphores
    for (i = 0; i < NUM_CHILDREN; i++)
    {
        if (sem_init(&sems[i], 1, 0) == -1)
        {
            perror("sem_init");
            exit(EXIT_FAILURE);
        }
    }
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
        // Wait for previous child processes to finish their turn
        if (i > 0)
        {
            if (sem_wait(&sems[i - 1]) == -1)
            {
                perror("sem_wait");
                exit(EXIT_FAILURE);
            }
        }
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

        // Release semaphore for next child process
        if (sem_post(&sems[i - 1]) == -1)
        {
            perror("sem_post");
            exit(EXIT_FAILURE);
        }

        printf("Child %d finishes with counter %d\n", i + 1, *shm);
        // release the turn
        exit(EXIT_SUCCESS);
    }

    // Parent process
    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        wait(NULL);
    }

    // Print the final value of the counter
    printf("Final counter value: %d\n", *shm);
    // Detach the shared memory segment for counter
    if (shmdt(shm) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Remove the shared memory segment for counter
    if (shmctl(ctrid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    // Destroy the semaphores
    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        if (sem_destroy(&sems[i]) == -1)
        {
            perror("sem_destroy");
            exit(EXIT_FAILURE);
        }
    }

    // Detach the shared memory segment for semaphores
    if (shmdt(sems) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    // Remove the shared memory segment for semaphores
    if (shmctl(semid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
