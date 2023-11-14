#include "a_shell.h"

/**
 * tokenise - splits a string into an array of words
 * @input: pointer to the string
 * @e_str: empty string
 *
 * Return: pointer to a char containing split words
 */

char **tokenise(char *input, const char *e_str)
{
	char **words = NULL, *copy = NULL, *token = NULL;
	int i, num = 0;

	copy = _strdup(input);
	if (!copy)
	{
		perror("Memory Allocation failure\n");
		free(copy);
		return (NULL);
	}

	words = malloc(sizeof(char *) * MAX_WORDS);
	if (!words)
	{
		free(words);
		return (NULL);
	}

	token = strtok(copy, e_str);
	while (token)
	{
		words[num] = _strdup(token);
		if (!words[num])
		{
			perror("Memory Allocation failure\n");
			for (i = 0; i < num; i++)
				free(words[i]);
			free(words);
			free(copy);
			return (NULL);
		}
		num++;
		token = strtok(NULL, " ");
	}
	free(copy);
	words[num] = NULL;
	return (words);
}

/**
 * _which - a function that finds executable files
 * @filename: executable file name to find
 *
 * Return: duplicate of the filepath, NULL if filepath can not be found
 */

char *_which(char *filename)
{
	char *path, *token;
	char filepath[BUFFER];
	struct stat st;

	path = _getenv("PATH");
	if (!path)
	{
		write(STDERR_FILENO, "Could not get path env variable.\n", 1);
		exit(1);
	}

	token = strtok(path, ":");
	while (token)
	{
		_strcpy(filepath, token); /* copy the dir path to filepath */
		_strcat(filepath, "/"); /* append a "/" to filepath */
		_strcat(filepath, filename); /* append filename to filepath */

		if (stat(filepath, &st) == 0)
			return (_strdup(filepath));
		token = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 *
 */

char *command_check(char *cmd, char *name)
{
	char *full_path;
	static int cmdCounter = 1;

	full_path = _which(cmd);
	if (!full_path)
	{
		cmd_error(cmdCounter, name, cmd);
		exit(127);
	}
	cmdCounter++;
	return (full_path);
}

/**
 *
 */

int exec(char **argv)
{
	pid_t child_pid;
	int status;
	char *name = "./hsh";
	char *fullPATH;
	static int cmdCounter = 1;

	if (!argv || !argv[0])
		return (0);
	if (access(argv[0], F_OK) == -1)
	{
		cmd_error(cmdCounter, name, argv[0]);
		exit(127);
	}

	child_pid = fork();
	if (child_pid == -1)
		fork_error(cmdCounter);
	if (child_pid == 0)
	{
		if (argv[0][0] == '/')
			execve(argv[0], argv, environ);
		else
		{
			fullPATH = command_check(argv[0], name);
			if (fullPATH)
			{
				free(argv[0]);
				argv[0] = fullPATH;
				if (execve(fullPATH, argv, environ) == -1)
					execve_error(cmdCounter, fullPATH,
						     argv[0]);
			}
			else
				freesplit(argv);
		}
	}
	waitpid(child_pid, &status, 0);
	cmdCounter++;
	return (WEXITSTATUS(status));
}
