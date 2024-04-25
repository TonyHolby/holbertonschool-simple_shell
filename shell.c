#include "shell.h"

/**
 * main - displays a prompt and waits for the user to type a command
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t length = 0;
	ssize_t read;
	char **argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		read = getline(&line, &length, stdin);

		if (read == -1)
		{
			break;
		}
		if (read == 1)
		{
			continue;
		}
		argv = tokenize_command(line);

		if (argv != NULL)
		{
			execute_command(argv);
		}
	}
	free(argv);
	free(line);
	return (0);
}
