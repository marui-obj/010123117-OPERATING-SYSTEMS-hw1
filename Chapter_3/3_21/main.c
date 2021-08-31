#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void fooFunction(int number)
{
    printf("%d\n", number);
    while(number > 1){
        if (number % 2 == 0){
            number = number / 2;
        }
        else{
            number = number*3+1;
        }
        printf("%d\n", number);
    }
}


int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    if(n <= 0){
        fprintf(stderr, "Input have to be positive\n");
        return -1;
    }

    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        /* Child process */
        fooFunction(n);
        printf("Child process ended\n");
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("Parent process ended\n");
    }
    return 0;

}
