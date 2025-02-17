#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // Child process
        printf("Child process (PID: %d) started\n", getpid());
        sleep(2);
        printf("Child process (PID: %d) finished\n", getpid());
        exit(0);
    }
    else
    {
        printf("Parent process (PID: %d) started\n", getpid());
        // sleep(3); // Uncomment this line to prevent zombie process
        printf("Parent process (PID: %d) finished\n", getpid());
        exit(0);
    }
    return 0;
}