#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Parent PID: %d\n", getppid());
    return 0;
}
