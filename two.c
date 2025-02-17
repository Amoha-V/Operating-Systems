#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

#define SHM_KEY 1234 // Correct shared memory key
#define SIZE 1024    // Define memory size

int main()
{
    // Access shared memory segment
    int shm_id = shmget(SHM_KEY, SIZE, 0666);
    if (shm_id == -1)
    {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory
    char *shm_ptr = (char *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    // Read and print message
    printf("Message read: %s\n", shm_ptr);

    // Detach from shared memory
    shmdt(shm_ptr);

    // Remove shared memory
    if (shmctl(shm_id, IPC_RMID, NULL) == -1)
    {
        perror("shmctl failed");
        exit(1);
    }

    printf("Shared memory removed\n");
    return 0;
}
