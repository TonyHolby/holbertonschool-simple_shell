#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_COMMAND_LENGTH 1024

void sigint_handler(int signum)
{
	printf("\nSIGINT signal : %d.\n", signum);
	exit(EXIT_FAILURE);
}

/**
 * main - Displays a prompt and waits for the user to type a command.
 * then executes the command typed by the user.
 *
 * Return: Always 0
 */

int main(void)
{
	char *line = NULL;
	size_t length = 0;
	ssize_t read;
	char *args[] = {NULL, NULL};
	pid_t pid;
	int status;

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("Handler errors failed");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#simple_shell$ ");
		read = getline(&line, &length, stdin);

		if (read == -1)
		{
			printf("\n");
			break;
		}
		if (read == 1)
		{
			continue;
		}
		line[read - 1] = '\0';
		pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			args[0] = line;
			args[1] = NULL;
			execve(line, args, NULL);
			perror("Execve failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (wait(&status) == -1)
			{
				perror("Wait failed");
				exit(EXIT_FAILURE);
			}
		}
	}
	free(line);
	return (0);
}
