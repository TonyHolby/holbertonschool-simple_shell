#include "shell.h"

/**
 * execute_command - executes the command typed by the user
 *
 * @argv: copy of command with arguments
 *
 * Return: Always 0
 */
int execute_command(char **argv)
{
	pid_t pid;
	char *args[] = {NULL, NULL};
	int status;

	if (argv[0] != NULL)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			args[0] = argv[0];
			args[1] = NULL;
			if (execve(args[0], args, NULL) == -1)
			{
				if (isatty(STDIN_FILENO))
				{
					perror("./hsh");
					exit(EXIT_FAILURE);
				}
				else
				{
					perror("execve failed");
					exit(EXIT_FAILURE);
				}
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	else
	{
		fprintf(stderr, "./hsh: %d: %s: not found\n", 1, argv[0]);
		exit(EXIT_FAILURE);
	}

	return (0);
}

