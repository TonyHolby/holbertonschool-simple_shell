#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 *
 *
 */

int main(void)
{
        char *line = NULL;
        size_t len = 0;
        ssize_t input_prompt = 0;

        while (input_prompt != -1)
        {
                printf("#cisfun$ ");
		input_prompt = getline(&line, &len, stdin);
                pid_t pid;

                pid = fork();
		if (pid < 0 )
		{
			perror("fork fail");
			exit(-1);
		}
		else if (pid == 0)
		{
			char *argv[] = {"sh", "-c", line, NULL};

			execve("/bin/sh", argv, NULL);
			perror("execve fail");
			exit(-1);
		}
		else
		{
			int status;

			wait(&status);
		}

                if (input_prompt == -1)
                {
                        printf("End of prompt!\n");
                        break;
                }
                printf("%s", line);

        }

        free(line);

        return (0);
}
