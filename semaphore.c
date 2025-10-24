 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/ipc.h>
 #include <sys/shm.h>
 #include <sys/types.h>
 #include <semaphore.h>
 #include <unistd.h>
 #include <sys/wait.h>
 int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *shared_str = (char*) shmat(shmid, (void*)0, 0);
    sem_t sem;
    sem_init(&sem, 0, 1);
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {
        sem_wait(&sem);
        printf("Child: Writing to shared memory...\n");
        sprintf(shared_str, "Hello from child process!");
        sem_post(&sem);
        shmdt(shared_str);
        exit(0);
    } else {
        wait(NULL);
        sem_wait(&sem);
        printf("Parent: Reading from shared memory: %s\n", shared_str);
        sem_post(&sem);
        shmdt(shared_str);
        shmctl(shmid, IPC_RMID, NULL);
        sem_destroy(&sem);
        printf("Parent: Cleaned up shared memory and semaphore.\n");
    }
    return 0;
 }
