#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * tokenize_command - a function that handles a command line with arguments.
 * @line: The command line typed by the user.
 * Return: The command on success and exit the function on failure.
 */

char **tokenize_command(char *line)
{
	char **command = NULL;
	char *token;
	int argc = 0;

	token = strtok(line, " \n");
	while (token != NULL)
	{
		command = realloc(command, (argc + 1) * sizeof(char *));
		if (command == NULL)
		{
			return (NULL);
		}

		command[argc] = strdup(token);
		if (command[argc] == NULL)
		{
			perror("Erreur lors de la copie du jeton");
			exit(EXIT_FAILURE);
		}
		argc++;
		token = strtok(NULL, " \n");
	}

	command = realloc(command, (argc + 1) * sizeof(char *));
	if (command == NULL)
	{
		return (NULL);
	}

	command[argc] = NULL;

	return (command);
}

/**
 * main - The main function of the simple shell.
 * @ac: The number of elements in the command typed by the user.
 * @argv: The NULL terminated array of elements in the command.
 * @env: The NULL terminated array of strings of the environment.
 * Return: 0 on success and exit the process on failure.
 */

int main(int ac, char **argv, char **env)
{
	pid_t pid;
	char *line = NULL;
	size_t len = 0;
	ssize_t input_prompt = 0;
	int status;

	while (input_prompt != -1)
	{
		printf("#simple_shell$ ");
		input_prompt = getline(&line, &len, stdin);

		if (input_prompt == -1)
		{
			printf("End of prompt!\n");
			break;
		}

		argv = tokenize_command(line);

		pid = fork();
		if (pid < 0)
		{
			perror("fork fail");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			char *path = getenv("PATH");
			char *token;
			char command_path[256];
			int found = 0;

			token = strtok(path, ":");
			while (token != NULL)
			{
				sprintf(command_path, "%s/%s", token, argv[0]);
				if (access(command_path, X_OK) == 0)
				{
					found = 1;
					break;
				}
				token = strtok(NULL, ":");
			}

			if (found == 1)
			{
				execve(command_path, argv, env);
				perror("execve fail");
				exit(EXIT_FAILURE);
			}
			else
			{
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}

		for (ac = 0; argv[ac] != NULL; ac++)
		{
			free(argv[ac]);
		}
		free(argv);
	}

	free(line);

	return (0);
}
