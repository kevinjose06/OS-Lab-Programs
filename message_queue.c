#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>
#define MAX 50

struct m_buffer
{
	long m_type;
	char m_text[MAX];
};

int main()
{
	pid_t id;
	key_t key;
	int msgid,l,i;
	char text[MAX],temp;
	struct m_buffer queue;

	key = ftok(".",67);
	msgid = msgget(key,0666 | IPC_CREAT);

	id = fork();

	if(id == 0)
	{
		msgrcv(msgid,&queue,sizeof(queue.m_text),1,0);
		l = strlen(queue.m_text);

		for(i = 0;i < (l / 2);i++)
		{
			temp = queue.m_text[i];
			queue.m_text[i] = queue.m_text[(l - i - 1)];
			queue.m_text[(l - i - 1)] = temp;
		}
		text[l] = '\0';

		queue.m_type = 2;
		msgsnd(msgid,&queue,sizeof(queue.m_text),0);
	}
	else
	{
		printf("Enter a string : ");
        	fgets(text,sizeof(text),stdin);
        	text[strcspn(text,"\n")] = '\0';

        	queue.m_type = 1;
        	strcpy(queue.m_text,text);

        	msgsnd(msgid,&queue,sizeof(queue.m_text),0);

		msgrcv(msgid,&queue,sizeof(queue.m_text),2,0);

		if(strcmp(text,queue.m_text) == 0)
		{
			printf("The string is a palindrome!\n");
		}
		else
		{
			printf("The string isn't a palindrome!\n");
		}
		wait(NULL);
		msgctl(msgid, IPC_RMID, NULL);
	}

	return 0;
}