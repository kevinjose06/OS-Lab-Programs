#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 200

struct shared_data
{
    char str1[50];
    char str2[50];
    char str3[50];
    char result[SIZE];
    int flag;
};

void flip_case(char *str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
        else if(str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 32;
    }
}

int main()
{

    int shmid;
    key_t key = ftok("shmfile", 65);

    shmid = shmget(key, sizeof(struct shared_data), 0666 | IPC_CREAT);
    struct shared_data *data = (struct shared_data*) shmat(shmid, NULL, 0);

    data->flag = 0;

    pid_t pid = fork();

    if(pid > 0)
    {
        printf("Enter first string: ");
        scanf(" %[^\n]", data->str1);

        printf("Enter second string: ");
        scanf(" %[^\n]", data->str2);

        printf("Enter third string: ");
        scanf(" %[^\n]", data->str3);

        data->flag = 1;
        while(data->flag != 2);

        flip_case(data->result);

        printf("\nFinal Output: %s\n", data->result);

        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
    }

    else if(pid == 0)
    {

        while(data->flag != 1);

        strcpy(data->result, data->str1);
        strcat(data->result, " ");
        strcat(data->result, data->str2);
        strcat(data->result, " ");
        strcat(data->result, data->str3);

        data->flag = 2;

        shmdt(data);
    }

    return 0;
}
