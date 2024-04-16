#include <stdio.h>
#include <unistd.h>

/**
 * main - prints the PID of the parent process
 *
 * Return: Always 0
 */

int main(void)
{
printf("Parent PID: %d\n", getppid());
return (0);
}
