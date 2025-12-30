/*Create a new process using a fork system call. Print the parent and child process IDs. Use
the pstree command to find the process tree for the child process starting from the init
process.
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        printf("Child process\n");
        printf("Parent PID : %d\n", getppid());
        printf("Child PID  : %d\n", getpid());
    }
    else if (pid > 0)
    {
        printf("Parent process\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);
    }
    else
    {
        printf("Error occurred!\n");
        return -1;
    }
    for(;;);

    return 0;
}

/*
1)Run the executable file.
2)Open new terminal and login
3)Give the command : pstree -ps <PID>
*/