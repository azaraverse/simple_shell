#include "a_shell.h"

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

	/* printf("displaying prompt: %s\n", prompt); */
	write(STDOUT_FILENO, prompt, _strlen(prompt));

	if (*line)
	{
		free(*line);
		*line = NULL;
	}

	*len = 0;
	read = getline(line, len, stdin);
	if (read == -1)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}

	input_length = _strcspn(*line, "\n");
	if (input_length < (size_t)read)
		(*line)[input_length] = '\0';
	/* printf("user input: %s\n", *line); */
	return (1);
}

/**
 * main - program entry point
 *
 * Return: Always 0.
 */

int main(void)
{
	/* pid_t child_pid; */
	char *fullPATH, *prompt = "#simple_shell$ ";
	char *line = NULL;
	/* char *name = "PATH", *value = "/usr/bin:/bin:/usr/sbin:/sbin"; */
	char **split;
	/* int status; */
	size_t len = 0;
	PathNode *pathList, *current;

	_setenv("PATH", "/usr/bin:/bin:/usr/sbin:/sbin", 1);
	pathList = get_PathList();
	while (1)
	{
		if (!_prompt(&line, &len, prompt))
			break;
		/* printf("main loop running...\n"); */

		/* path = _getenv("PATH"); */
		split = tokenise(line, " \n");
		if (!split || !split[0])
			exec(split);
		else
		{
			if (split[0][0] == '/')
				fullPATH = _strdup(split[0]);
			else
				fullPATH = _which(split[0]);
			if (fullPATH)
			{
				free(split[0]);
				split[0] = fullPATH;
				exec(split);
			}
			else
				freesplit(split);
		}
		current = pathList;
		while (current)
			current = current->next;
	}
	freelist(pathList);
	free(line);
	/* printf("program ended\n"); */
	return (0);
}
