#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	pid_t pid;
	int i;
	pid = fork();
    	if (pid < 0)
	{
        	printf("Fork failed\n");
        	return 1;
    	}

    	if (pid == 0)
	{

        	char **args = malloc((argc + 1) * sizeof(char *));
		args[0] = "./myadder";
		for(i=1;i<argc;i++)
		{
			args[i] = argv[i];
		}
		args[argc] = NULL;
		execvp(args[0],args);
    	}
    	else
	{
        	wait(NULL);
    	}

    	return 0;
}
