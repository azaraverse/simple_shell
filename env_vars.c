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

	if (!environ)
		return (NULL);

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
	return (0);
}

/**
 * starts_with - a function that checks if one string starts with another
 * @s: pointer to string to be compared with prefix
 * @prefix: pointer to string to compare with s
 *
 * Return: 1 to start with prefix, 0 to ignore.
 */

int starts_with(const char *s, const char *prefix)
{
	while (*prefix)
	{
		if (*prefix != *s)
			return (0);
		prefix++;
		s++;
	}
	return (1);
}

/**
 * _setenv - a function that sets the value of an env variable
 * @name: pointer to the environment variable name
 * @value: pointer to the value to set the env variable
 * @overwrite: overwrite value
 *
 * Return: 0 on success, -1 on failure
 */

int _setenv(char *name, char *value, int overwrite)
{
	char *new_env; /* *old_env */
	unsigned int i;

	if (!name || !value)
		return (-1);
	i = 0;
	while (*environ[i])
	{
		if (starts_with(environ[i], name))
		{
			if (overwrite)
			{
				new_env = malloc(_strlen(name) +
						 _strlen(value) + 2);
				if (new_env == NULL)
					return (-1);

				_strcpy(new_env, name);
				_strcat(new_env, "=");
				_strcat(new_env, value);

				environ[i] = new_env;
				return (0);
			}
			else
				return (0);
		}
		i++;
	}
	new_env = malloc(_strlen(name) + _strlen(value) + 2);
	if (new_env == NULL)
		return (-1);

	_strcpy(new_env, name);
	_strcat(new_env, "=");
	_strcat(new_env, value);

	environ[i] = new_env;
	environ[i + 1] = NULL;
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
