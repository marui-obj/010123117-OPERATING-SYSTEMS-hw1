#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100

int main()
{
	pid_t pid;
	pid = fork();
	if (pid < 0){
		printf("\nFork Failed\n");
		return 1;
	}

	else if (pid == 0){
		execlp("/bin/ps", "ps -l", NULL);
	}

	return 0;

}
