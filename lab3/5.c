#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int fds[2];
	char buf[10];
	int count;
	int i;
	pipe(fds);
	if (fork() == 0) {
		close(fds[0]);
		printf("Please input a sentence: \n");
		while ((count = read(0, buf, 10)) > 0) {
           		write(fds[1], buf, 10);
			memset(buf, 0, 10);
		}
		exit(0);
	}
	else if (fork() == 0) {
		close(fds[1]);
		while((count = read(fds[0], buf, 10)) > 0) {
			printf("Consumed: \n");
			printf("%s", buf);
			printf("\n");
			
		}
		exit(0);
	}
	else {
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}
