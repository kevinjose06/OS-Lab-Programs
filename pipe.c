/*Using Pipe – Evaluate the expression sqrt(b^2-4ac). The first process
evaluates b^2. The second process evaluates 4ac and sends it to the first
process which evaluates the final expression and displays it*/

#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<sys/wait.h>

int main()
{
	int a,b,c,val1,desc;
	double f;
	pid_t id;
	int fd[2];

	printf("Enter the values of a,b and c : ");
	scanf("%d%d%d",&a,&b,&c);

	pipe(fd);
	id = fork();

	if(id == 0)
	{
		close(fd[0]);
		val1 = (4 * a * c);
		write(fd[1],&val1,sizeof(int));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		read(fd[0],&val1,sizeof(int));
		b *= b;
		desc = (b - val1);
		if(desc < 0)
		{
			printf("Discriminant not available!\n");
			close(fd[0]);
			wait(NULL);
			return -1;
		}
		f = sqrt(desc);
		printf("The value is : %f\n",f);
		close(fd[0]);
		wait(NULL);
	}

	return 0;
}
