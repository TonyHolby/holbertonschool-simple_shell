#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * verify_path - a function that verify the PATH of the command.
 * @argv: An array of the duplicate command.
 * Return: exit with a success signal or return 0.
 */

int verify_path(char **argv)
{
	char *path = getenv("PATH");
	char *token;
	char command_path[256];

	token = strtok(path, ":");
	while (token != NULL)
	{
		sprintf(command_path, "%s/%s", token, argv[0]);
		if (access(command_path, X_OK) == 0)
		{
			perror("verify_path fail");
			exit(EXIT_SUCCESS);
		}
		token = strtok(NULL, ":");
	}

	return (0);
}

/**
 * execute_command - a function that executes a command if the PATH exists.
 * @argv: An array of the duplicate command.
 * @env: The environment variable.
 */

void execute_command(char **argv, char **env)
{
	pid_t pid;
	int status, ac;

	if (verify_path(argv))
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork fail");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(argv[0], argv, env);
			perror("execve fail");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}
	else
	{
		perror("Command not found or not executable.\n");
		exit(EXIT_FAILURE);
	}

	for (ac = 0; argv[ac] != NULL; ac++)
	{
		free(argv[ac]);
	}

	free(argv);
}

/**
 * tokenize_command - a function that handles a command line with arguments.
 * @line: The command line typed by the user.
 * Return: The command on success and exit the process on failure.
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
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		command[argc] = strdup(token);
		if (command[argc] == NULL)
		{
			perror("Error copying token");
			exit(EXIT_FAILURE);
		}
		argc++;
		token = strtok(NULL, " \n");
	}

	command = realloc(command, (argc + 1) * sizeof(char *));
	if (command == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	command[argc] = NULL;

	if (command[0] == NULL)
	{
		perror("command NULL");
		exit(EXIT_FAILURE);
	}

	return (command);
}

/**
 * main - The main function of the simple shell.
 * Return: Always 0.
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t input_prompt = 0;
	char **argv;
	char **env = NULL;

	while (input_prompt != -1)
	{
		printf("#simple_shell$ ");
		input_prompt = getline(&line, &len, stdin);

		if (input_prompt == -1)
		{
			break;
		}

		argv = tokenize_command(line);
		if (argv != NULL)
		{
			execute_command(argv, env);
		}
		else
		{
			perror("execute_command fail");
		}
	}

	free(line);

	return (0);
}

