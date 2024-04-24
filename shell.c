#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 *
 *
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
                    exit (EXIT_FAILURE);
                }
            }
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }
    else
    {
        fprintf(stderr, ": %d : command not found : %s\n", 1, args[0]);
        exit(EXIT_FAILURE);
    }

    return (0);
}
/**
 *
 *
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

    return (command);
}
/**
 *
 *
 */
int main(void)
{
        char *line = NULL;
        size_t length = 0;
        ssize_t read;
        char **argv;

        while (1)
        {
                if (isatty(STDIN_FILENO))
                        printf("$ ");
                read = getline(&line, &length, stdin);

                if (read == -1)
                {
                        break;
                }
                if (read == 1)
                {
                        continue;
                }

        argv = tokenize_command(line);

        if (argv != NULL)
        {
            execute_command(argv);
        }
    }

    free(argv);
    free(line);

    return (0);
}

