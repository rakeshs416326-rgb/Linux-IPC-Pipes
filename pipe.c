#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pid_t pid;
    char message[] = "Hello Rakesh";
    char buffer[100];

    pipe(fd);   // Create pipe

    pid = fork();   // Create child process

    if (pid == 0)
    {
        // Child process - Read from pipe
        close(fd[1]);   // Close write end

        read(fd[0], buffer, sizeof(buffer));
        printf("Child read: %s\n", buffer);

        close(fd[0]);
    }
    else
    {
        // Parent process - Write to pipe
        close(fd[0]);   // Close read end

        write(fd[1], message, strlen(message) + 1);
        printf("Parent wrote: %s\n", message);

        close(fd[1]);
        wait(NULL);   // Wait for child process
    }

    return 0;
}
