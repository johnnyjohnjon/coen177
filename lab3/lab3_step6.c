#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fds[2];
    pipe(fds);
    char buff[60];
    memset(buff, 0, sizeof(buff));

    if (fork() == 0)
    {
        printf("Send a message:\n");
        close(fds[0]);
        int i = read(0, buff, 60);
        while (i > 0)
        {
            write(fds[1], buff, 60);
            i = read(0, buff, 60);
        }
        exit(0);
    }
    else if (fork() == 0)
    {
        close(fds[1]);
        int i = read(fds[0], buff, 60);
        while (i > 0)
        {
            printf("Consumer Output:\n%s\n", buff);
            i = read(fds[0], buff, 60);
        }
        exit(0);
    }
    else
    {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
}
