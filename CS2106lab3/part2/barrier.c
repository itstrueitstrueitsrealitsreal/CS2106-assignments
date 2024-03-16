#include <stdio.h>
#include <semaphore.h>
#include "barrier.h"
#include <sys/ipc.h>
#include <sys/shm.h>

int nproc = 0, *count = 0;
sem_t *barrier, *mutex;
int count_shmid, bar_shmid, mutex_shmid;

void init_barrier(int numproc) {
    nproc = numproc;
    count_shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);
    count = (int*) shmat(count_shmid, NULL, 0);
    count = 0;

    bar_shmid = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | 0600);
    barrier = (sem_t*) shmat(bar_shmid, NULL, 0);
    sem_init(barrier, 0, 0);

    mutex_shmid = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | 0600);
    mutex = (sem_t*) shmat(mutex_shmid, NULL, 0);
    sem_init(mutex, 1, 1);

}

void reach_barrier() {
    // todo: protect count using a mutex
    sem_wait(mutex);
    (*count)++;
    sem_post(mutex);
    if ((*count) == nproc) {
        sem_post(barrier);
    } else {
        sem_wait(barrier);
        sem_post(barrier);
    }
}

void destroy_barrier(int my_pid) {
    if(my_pid != 0) {
        // Destroy the semaphores and detach
        // and free any shared memory. Notice
        // that we explicitly check that it is
        // the parent doing it.
        sem_destroy(barrier);
        sem_destroy(mutex);
        shmdt((char*)count);
        shmctl(count_shmid, IPC_RMID, 0);
        shmdt(barrier);
        shmctl(bar_shmid, IPC_RMID, 0);
        shmdt(mutex);
        shmctl(mutex_shmid, IPC_RMID, 0);
    }
}


