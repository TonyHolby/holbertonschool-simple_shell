#include <stdio.h>

/**
 * main - prints all the arguments
 *
 * @av: pointer to an array of character pointers
 * @ac: number of arguments
 *
 * Return: Always 0
 */

int main(int ac, char **av)
{
	char **arg = av;

	while (*arg != NULL)
	{
		printf("%s\n", *arg);
		arg++;
	}

	return (0);
}
