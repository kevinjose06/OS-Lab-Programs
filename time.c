/*Write a simple program to print the system time and execute it. Then use the /proc file
system to determine how long this program (in the strict sense, the corresponding process)
ran in user and kernel modes.*/

#include <stdio.h>
#include <time.h>
#include<unistd.h>

int main()
{
        time_t t;
        pid_t pid;

        pid = getpid();
        time(&t);
        printf("PID : %d\n",pid);
        printf("Current system time: %s\n",ctime(&t));
        for(;;);
        return 0;
}

/*After compiling and executing:
    1)Open a new terminal and login to server.
    2)Give the command : cat /proc/<PID>/stat.
    3)The output of (2) gives the entire information of the process which are represented in column format,
    out of which the 14th and 15th column give the user mode clock tick and kernel mode clock tick.
    4)Give the command : awk '{print "User mode : ",$14,"Kernel mode : ",$15}' /proc/<PID>/stat
    5)This give the clock time in ticks.
    6)Check clock ticks per second:
        getconf CLK_TCK
        Suppose it outputs 100,
        Then:
        User time   = utime / 100 seconds
        Kernel time = stime / 100 seconds.
*/
    