#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

int main(void)
{
	char *command;
	size_t command_len = MAX_COMMAND_LENGTH;

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

		ssize_t read = getline(&command, &command_len, stdin);

		if (read == -1)
		{
			break;
		}
		command[read - 1] = '\0';
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			char *args[] = {command, NULL};
			execve(command, args, NULL);
			perror("Execve failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}

	free(command);
	return 0;
}
