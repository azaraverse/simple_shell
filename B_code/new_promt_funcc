#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _prompt - displays a prompt and reads user input
 * @line: double pointer to store user's input
 * @len: pointer to size_t variable to keep track of length of buffer pointed
 * to by line
 * @prompt: prompt to display to stdout
 *
 * Return: 1 on success, 0 otherwise
 */

int _prompt(char **line, size_t *len, char *prompt)
{
	size_t input_length;
	ssize_t read;

	if (_isatty(STDIN_FILENO)) {
		write(STDOUT_FILENO, prompt, _strlen(prompt));
		read = getline(line, len, stdin);
	} else {
		// Read from standard input without displaying a prompt
		read = getline(line, len, stdin);
	}

	if (read == -1)
	{
		write(STDOUT_FILENO, "\n", 1);
		return 0;
	}

	input_length = _strcspn(*line, "\n");
	if (input_length < (size_t)read)
		(*line)[input_length] = '\0';

	return 1;
}

