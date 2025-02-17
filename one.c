#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_KEY 1234 // Define a proper key
#define SIZE 1024    // Define the correct size

int main()
{
    // Create shared memory segment
    int shm_id = shmget(SHM_KEY, SIZE, IPC_CREAT | 0666);
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

    printf("Enter message: ");
    fgets(shm_ptr, SIZE, stdin);

    // Remove newline character if present
    shm_ptr[strcspn(shm_ptr, "\n")] = 0;

    printf("Message written: %s\n", shm_ptr);

    // Detach from shared memory
    shmdt(shm_ptr);

    return 0;
}
