#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if(pid > 0)
    {
        printf("Parent PID = %d\n", getpid());
        sleep(300);
    }
    else
    {
        printf("Child exiting...\n");
        exit(0);
    }

    return 0;
}
