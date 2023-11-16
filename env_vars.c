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
 * _realloc - a function that resizes the memory pointed to a pointer allocated
 * by malloc
 * @ptr: pointer address
 * @old_size: previous size of alloaction
 * @new_size: new size of alloaction
 * Return: void
 */

void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *newPtr;
	size_t copySize;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	newPtr = malloc(new_size);
	if (ptr != NULL)
	{
		copySize = (old_size < new_size) ? old_size : new_size;
		memcpy(newPtr, ptr, copySize);
		free(ptr);
	}
	return (newPtr);
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
 * @var: pointer to the environment variable name
 * @value: pointer to the value to set the env variable
 *
 * Return: 0 on success, -1 on failure
 */

int _setenv(char *var, char *value)
{
	char *new_env;
	int i, num_vars;
	size_t len;

	if (!var || !value)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		if (starts_with(environ[i], var))
		{
			len = _strlen(var) + _strlen(value) + 2;
			if (len <= (size_t)_strlen(environ[i]))
			{
				_strcpy(environ[i], var);
				_strcat(environ[i], "=");
				_strcat(environ[i], value);
			}
			else
			{
				new_env = _realloc(environ[i],
						   _strlen(environ[i]), len);
				if (!new_env)
				{
					write(STDERR_FILENO,
					      "memory alloc fail\n", 18);
					return (-1);
				}
				_strcpy(environ[i], var);
				_strcat(environ[i], "=");
				_strcat(environ[i], value);
			}
			return (0);
		}
	}
	new_env = malloc(_strlen(var) + _strlen(value) + 2);
	if (!new_env)
	{
		write(STDERR_FILENO, "memory alloc fail\n", 18);
		return (-1);
	}
	_strcpy(new_env, var);
	_strcat(new_env, "=");
	_strcat(new_env, value);

	num_vars = 0;
	while (environ[num_vars])
		num_vars++;
	environ = _realloc(environ, num_vars * sizeof(char *),
			   (num_vars + 2) * sizeof(char *));
	if (environ == NULL)
	{
		write(STDERR_FILENO, "memory alloc fail\n", 18);
		free(new_env);
		return (-1);
	}
	environ[num_vars] = new_env;
	environ[num_vars + 1] = NULL;
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
