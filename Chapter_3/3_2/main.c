#include <stdio.h>
#include <unistd.h>

int main()
{
    fork();

    fork();

    fork();

    printf("HELLO_WORLD\n");
    return 0;
}
