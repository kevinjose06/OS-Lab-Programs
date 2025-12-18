/*Create a new process using a fork system call. The child process should print the string
“PCCSL407” and the parent process should print the string “Operating Systems Lab”.
Use a wait system call to ensure that the output displayed is “PCCSL407 Operating
Systems Lab” */

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
        pid_t pid;

        pid = fork();

        if(pid == 0)
        {
                printf("PCCSL4O7 ");
        }
        else if(pid > 0)
        {
                wait(NULL);
                printf("Operating Systems Lab\n");
        }
        else
        {
                printf("Error occured!\n");
                return -1;
        }
        return 0;
}


