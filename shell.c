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
        pid_t pid;
	char *line = NULL;
        size_t len = 0;
        ssize_t input_prompt = 0;
	char *argv[] = {"/bin/sh", NULL};
	int status;

        while (input_prompt != -1)
        {
                printf("#cisfun$ ");
		input_prompt = getline(&line, &len, stdin);

                pid = fork();
		if (pid < 0 )
		{
			perror("fork fail");
			exit(-1);
		}
		else if (pid == 0)
		{
			execve(argv[0], argv, NULL);
			perror("execve fail");
			exit(-1);
		}
		else
		{
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
