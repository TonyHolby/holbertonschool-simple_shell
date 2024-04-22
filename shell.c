#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

/**
 * main - Displays a prompt and waits for the user to type a command.
 * then executes the command typed by the user.
 *
 * Return: Always 0
 */

int main(void)
{
	char *command = NULL;
	size_t command_len = MAX_COMMAND_LENGTH;
	ssize_t read;
	char *args[] = {NULL, NULL};
	pid_t pid;

	command = (char *)malloc(command_len * sizeof(char));
	if (command == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#simple_shell$ ");
		read = getline(&command, &command_len, stdin);

		if (read == -1)
		{
			break;
		}
		command[read - 1] = '\0';
		pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			args[0] = command;
			args[1] = NULL;
			execve(command, args, NULL);
			perror("Execve failed");
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
	}
	free(command);
	return (0);
}
