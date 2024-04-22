#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define COMMAND_MAX_LENGTH 1024

/**
 * main - Displays a prompt and waits for the user to type a command.
 * then executes the command the user has typed.
 *
 * Return: Always 0
 */

int main(void)
{
	char command[COMMAND_MAX_LENGTH];

	while (1)
	{
		printf("#simple_shell$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("End of prompt!\n");
			break;
		}
		command[strcspn(command, "\n")] = '\0';
		if (system(command) == -1)
		{
			fprintf(stderr, "Erreur : commande introuvable\n");
		}
	}

	return (0);
}
