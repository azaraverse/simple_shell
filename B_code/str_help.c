#include "a_shell.h"

/**
 * _strlen - returns the length of a string
 * @s: pointer to the string
 *
 * Return: length of the string
 */

int _strlen(char *s)
{
	if (*s != '\0')
		return (1 + _strlen(s + 1));
	else
		return (0);
}

/**
 * _strcspn - a function that returns the length of a segment of a string that
 * does not contain any of the chars in the specified set
 * @s: pointer to the string to check
 * @reject: pointer to the specified set
 *
 * Return: length of string not in specified set
 */

size_t _strcspn(const char *s, const char *reject)
{
	size_t char_index, len = 0;

	while (s[len] != '\0')
	{
		char_index = 0;
		while (reject[char_index] != '\0')
		{
			if (s[len] == reject[char_index])
				return (len);
			char_index++;
		}
		len++;
	}
	return (len);
}

/**
 * _strdup - returns a pointer to a newly alloacted space in memory, which
 * contains a copy of the string given as a parameter
 * @s: pointer to the string
 *
 * Return: pointer to duplicated string on success
 */

char *_strdup(char *s)
{
	int i, j;
	char *array;

	if (!s)
		return (NULL);

	i = 0;
	while (s[i] != '\0')
		i++;

	array = malloc((i + 1) * sizeof(char));
	if (!array)
		return (NULL);

	j = 0;
	while (j < i)
	{
		array[j] = s[j];
		j++;
	}
	array[i] = '\0';
	return (array);
}

/**
 * _strcpy - a function that copies the string pointed to by src to dest
 * @dest: destination pointer to store copied string
 * @src: source pointer to store copied string
 *
 * Return: a pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	i = -1;
	do {
		i++;
		dest[i] = src[i];
	} while (src[i] != '\0');

	return (dest);
}

/**
 * _strcat - a function that concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: dest
 */

char *_strcat(char *dest, char *src)
{
	char *s = dest;

	while (*dest != '\0')
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (s);
}
