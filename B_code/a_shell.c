#include "a_shell.h"

/**
 * _isatty - a function that checks if stdin is associated with a terminal
 * @fd: file descriptor to check against isatty.
 *
 * Return: void.
 */

int _isatty(int fd)
{
	return (isatty(fd));
}

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

	if (_isatty(STDIN_FILENO))
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
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	char *fullPATH, *prompt = "#simple_shell$ ";
	char *line = NULL;
	char **split;
	size_t len = 0;
	PathNode *pathList, *current;
	(void)argc;

	_setenv("PATH", "/usr/bin:/bin:/usr/sbin:/sbin", 1);
	pathList = get_PathList();
	while (1)
	{
		if (_prompt(&line, &len, prompt))
		{
			if (line && *line && line[0] != '\0')
			{
				split = tokenise(line, " \n");
				if (!split || !split[0])
				{
					exec(split);
					freesplit(split);
				}
				else
				{
					if (split[0][0] == '/')
						fullPATH = _strdup(split[0]);
					else
						fullPATH =
							command_check(split[0],
								      argv[0]);
					if (fullPATH)
					{
						free(split[0]);
						split[0] = fullPATH;
						exec(split);
					}
					else
						freesplit(split);
				}
			}
			current = pathList;
			while (current)
				current = current->next;
		}
		else
			break;
	}

	freelist(pathList);
	free(line);
	return (0);
}
