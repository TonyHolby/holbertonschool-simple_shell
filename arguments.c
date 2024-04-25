#include "shell.h"

/**
 * tokenize_command - creates a copy of the command with the arguments
 *
 * @line: store what the user types
 *
 * Return: copy of the line typed by user
 */
char **tokenize_command(char *line)
{
	char **command = NULL;
	char *token;
	int argc = 0;

	token = strtok(line, "\n");
	while (token != NULL)
	{
		command = realloc(command, (argc + 1) * sizeof(char));
		if (command == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		command[argc] = strcpy(token, line);
		if (command[argc] == NULL)
		{
			perror("Error copying token");
			exit(EXIT_FAILURE);
		}
		argc++;
		token = strtok(NULL, "\n");
	}
	command = realloc(command, (argc + 1) * sizeof(char));
	if (command == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	command[argc] = NULL;

	if (command[0] == NULL)
	{
		printf("\n");
		exit(EXIT_FAILURE);
	}
	if (strcmp(command[0], "exit") == 0)
		exit(EXIT_SUCCESS);

	return (command);
}
