/*Write a program to add two integers (received via the command line) and compile it to an
executable named “myadder”. Now write another program that creates a new process
using a fork system call. Make the child process add two integers by replacing its image
with the “myadder” image using execvp system call.*/

#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
        int i,s;
        s = 0;
        for(i=1;i<argc;i++)
        {
                s += atoi(argv[i]);
        }
        printf("Sum : %d\n",s);
        return 0;
}

//I modified this question to add any number of integers received from the commmand line.