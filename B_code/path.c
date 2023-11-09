#include "a_shell.h"

/**
 * _getenv - function that gets the current environment variable
 * @name: pointer to the environment variable given
 *
 * Return: 0 on success
 */

char *_getenv(const char *name)
{
	char *value;
	unsigned int i, j;

	i = 0;
	while (*environ[i])
	{
		j = 0;
		if (name[j] == environ[i][j])
		{
			while (name[j])
			{
				if (name[j] != environ[i][j])
					break;
				j++;
			}
			if (name[j] == '\0')
			{
				value = (environ[i] + j + 1);
				return (value);
			}
		}
		i++;
	}
	return (NULL);
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
		{
			return _strdup(filepath);
		}
		token = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 *
 */

PathNode *add_PathNode_end(PathNode *head, char *dir)
{
	PathNode *addNode, *current;

	if (!head)
		return (NULL);

	addNode = malloc(sizeof(PathNode));
	if (!addNode)
	{
		perror("Memory allocation failure");
		exit(EXIT_FAILURE);
	}

	addNode->directory = _strdup(dir);
	addNode->next = NULL;

	if (!head)
		head = addNode;
	else
	{
		current = head;
		while (current->next)
			current = current->next;
		current->next = addNode;
	}
	return (head);
}

/**
 *
 */

PathNode *get_PathList(void)
{
	PathNode *pathList = NULL;
	char *path, *token;

	path = _getenv("PATH");
	if (path)
	{
		token = strtok(path, ":");
		while (token)
		{
			pathList = add_PathNode_end(pathList, token);
			token = strtok(NULL, ":");
		}
	}
	return (pathList);
}
