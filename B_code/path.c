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
 * add_PathNode_end - a function that adds a new node at the end of PathNode
 * list
 * @head: pointer to a memory location held by head
 * @dir: str to insert into head
 *
 * Return: head.
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
 * get_PathList - a function that gets the path list of a stated PATH
 * Return: pointer to the path list.
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

/**
 * _setenv - a function that sets the value of an env variable
 * @name: pointer to the environment variable name
 * @value: pointer to the value to set the env variable
 *
 * Return: 0 on success, -1 on failure
 */

int _setenv(char *name, char *value)
{
	char *new_env;
	unsigned int i, j, k;

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
				free(environ[i]);
				new_env = malloc(_strlen(name) +
						 _strlen(value) + 2);
				if (new_env == NULL)
					return (-1);
				k = 0;
				while (name[k])
				{
					new_env[k] = name[k];
					k++;
				}
				new_env[k++] = '=';
				k = 0;
				while (value[k])
				{
					new_env[k] = value[k];
					k++;
				}
				new_env[k] = '\0';
				environ[i] = new_env;
				return (0);
			}
		}
		i++;
	}
	new_env = malloc(_strlen(name) + _strlen(value) + 2);
	if (new_env == NULL)
		return (-1);
	k = 0;
	while (name[k])
	{
		new_env[k] = name[k];
		k++;
	}
	new_env[k++] = '=';
	k = 0;
	while (value[k])
	{
		new_env[k] = value[k];
		k++;
	}
	new_env[k] = '\0';
	environ[i] = new_env;
	return (0);
}

/**
 * _unsetenv - a function that unsets an env variable
 * @name: pointer to the env variable name
 *
 * Return: 0 on success, -1 on failure
 */

int _unsetenv(char *name)
{
	unsigned int i, j;
	unsigned int numDigits = 0;

	while (environ[numDigits])
		numDigits++;

	for (i = 0; i < numDigits - 1; i++)
	{
		for (j = 0; name[j] != '\0'; j++)
		{
			if (environ[i][j] != name[j])
				break;
		}
	}

	if (environ[i][j] == '\0')
	{
		free(environ[i]);
		for (j = i; j < numDigits - 1; j++)
			environ[j] = environ[j + 1];
		environ[numDigits - 1] = NULL;
		return (0);
	}
	return (-1);
}
