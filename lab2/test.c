#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <signal.h>
int id;
struct Mesg
{
    char message[40];
    int count;
    char token[10][20];
    char sorttoken[10][20];
};

#define KEY ((key_t)(713))
#define SEGSIZE sizeof(struct Mesg)

void cleanup(int sigtype)
{
    shmdt(0);
    printf("\n Terminating\n");
    execlp("ipcrm", "ipcrm", "-M", "713", (char *)(0));
    printf("ERROR!");
    exit(0);
}

int main(int argc, char *argv[])
{
    int i, j;
    int count;
    char *token;
    char tmp[20];
    struct Mesg *msg;
    struct shmid_ds shmbuf;
    signal(SIGINT, cleanup);
    signal(SIGQUIT, cleanup);
    id = shmget(KEY, SEGSIZE, IPC_CREAT | 0666);
    if (id < 0)
    {
        perror("shmget failed 1\n");
        exit(1);
    }
    msg = (struct Mesg *)shmat(id, 0, 0);
    if (msg <= (struct Mesg *)(0))
    {
        perror("shma failed 2\n");
        exit(1);
    }
    msg->count = 0;
    strcpy(msg->message, "Welcome to COEN 177 Operating Systems");
    count = strlen(msg->message);
    if (fork() == 0)
    {
        msg->count = 1;
        for (i = 0; i < count; i++)
            if (msg->message[i] == ' ')
                msg->count++;
        exit(0);
    }
    else if (fork() == 0)
    {
        i = 0;
        token = strtok(msg->message, " ");
        while (token != NULL)
        {
            strcpy(msg->token[i], token);
            i++;
            token = strtok(NULL, " ");
        }
        exit(0);
    }
    else if (fork() == 0)
    {
        for (i = 0; i < msg->count; i++)
        {
            strcpy(tmp, msg->token[i]);
            strcpy(msg->sorttoken[i], tmp);
        }
        for (i = msg->count - 1; i >= 0; i--)
        {
            for (j = 0; j < i; j++)
            {
                if (strcmp(msg->sorttoken[j], msg->sorttoken[j + 1]) > 0)
                {
                    strcpy(tmp, msg->sorttoken[j]);
                    strcpy(msg->sorttoken[j], msg->sorttoken[j + 1]);
                    strcpy(msg->sorttoken[j + 1], tmp);
                }
            }
        }
        for (i = 0; i < msg->count; i++)
        {
            printf("%s ", msg->sorttoken[i]);
        }
        exit(0);
    }
    for (i = 0; i < 3; i++)
        wait(0);
    return 0;
}