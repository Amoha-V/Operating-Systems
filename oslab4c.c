#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork(); // Create child process

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) // Child process
    {
        sleep(5); // Sleep to allow parent to exit
        printf("Child process (PID: %d, PPID: %d) is now an orphan, adopted by init/systemd.\n", getpid(), getppid());
        exit(0);
    }
    else // Parent process
    {
        printf("Parent process (PID: %d) is exiting.\n", getpid());
        exit(0);
    }

    return 0;
}
