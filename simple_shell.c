#include "simple_shell.h"

/**
 * main - program entry point
 *
 * Return: Always 0
 */
int main (void)
{
	char input[MAX_INPUT_LENGTH], *d, *newline_position, *args[2];
	pid_t pid;

	while (1)
	{
		write(STDOUT_FILENO, "simple_shell$ ", 14);
		d = fgets(input, MAX_INPUT_LENGTH, stdin);

		if (d == NULL)
		{
			write(STDOUT_FILENO, "\n", 1); /* handle EOF (Ctrl+D) */
			break;
		}
		/* remove the newline character */
		newline_position = _strchr(input, '\n');
		if (newline_position != NULL)
			*newline_position = '\0';
		if (_strlen(input) > 0) /* execute the command using execve */
		{
			pid = fork();

			if (pid == 0)
			{
				/* child process */
				args[0] = input;
				args[1] = NULL;

				execve(input, args, NULL);
				/* if execve fails */
				command_error(input);
			}
			else if (pid > 0)
				/* parent process */
				wait(NULL);
			else
				fork_error(); /* fork failed */
		}
	}
	return (0);
}
