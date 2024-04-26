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
		if (isatty(STDIN_FILENO)) /*checks whether the function is in interactive mode*/
			printf("$ ");
		read = getline(&line, &length, stdin); /*stores the command and allocates memory*/

		if (read == -1)
		{
			break; /*stops the function*/
		}
		if (read == 1)
		{
			continue;
		}
		argv = tokenize_command(line); /*creates a copy of the command with the arguments*/

		if (argv != NULL)
		{
			execute_command(argv); /*executes the command typed by the user*/
		}
		free(argv);
		free(line);
	}
	return (0);
}
