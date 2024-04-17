#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - executes the command ls -l /tmp
 * in 5 different child processes
 *
 * Return: Always 0
 */

int main(void)
{
	int i;
	pid_t pid;

	for (i = 0; i < 5; i++)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			printf("Child process %d with PID: %d\n", i + 1, getpid());
			char *args[] = {"ls", "-l", "/tmp", NULL};

			execve("/bin/ls", args, NULL);
			perror("Execve failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			int status;

			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				printf("Child process %d exited with status: %d\n",
						i + 1, WEXITSTATUS(status));
			}
			else
			{
				printf("Child process %d terminated abnormally\n", i + 1);
			}
		}
	}
	return (0);
}
