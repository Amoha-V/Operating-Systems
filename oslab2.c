#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    // open
    int fd = open("file.h", O_CREAT | O_RDWR, 0666);
    if (fd == -1)
    {
        perror("open failed");
        exit(1);
    }
    printf("file opened %d\n", fd);
    // write
    const char *msg = "Hello world";
    ssize_t word = write(fd, msg, 11);
    if (word == -1)
    {
        perror("write failed");
        close(fd);
        exit(1);
    }
    printf("no of byte: %ld\n", word);
    // lseek
    off_t offset = lseek(fd, 0, SEEK_SET);
    if (offset == -1)
    {
        perror("lseek failed");
        close(fd);
        exit(1);
    }
    printf("file offset set to %ld\n", offset);
    // read
    char buffer[50];
    lseek(fd, 0, SEEK_SET); // Move to the start of the file for reading
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1)
    {
        perror("read failed");
        close(fd);
        exit(1);
    }
    buffer[bytes_read] = '\0';
    printf("Read from file: %s\n", buffer);
    // fork
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        close(fd);
        exit(1);
    }
    // pid(child process)
    if (pid == 0)
    {
        printf("Child process, PID: %d\n", getpid());
        exit(0);
    }
    // pid(panrent process)
    else
    {
        int status;
        wait(&status); // wait
        printf("Parent process, PID: %d\n", getpid());
        printf("Child process terminated with status: %d\n", WEXITSTATUS(status));
    }
    // exec
    if (fork() == 0)
    {
        execlp("ls", "ls", "-l", NULL);
        perror("exec failed");
        exit(1);
    }
    // sleep
    printf("Sleeping for 2 seconds...\n");
    sleep(2);
    printf("Awoke after 2 seconds\n");
    // getpid
    pid_t current_pid = getpid();
    printf("Current process ID: %d\n", current_pid);

    close(fd);
}