#include "a_shell.h"

/**
 * _strcmp - a function that compares two strings
 * @str1: pointer to string to compare
 * @str2: pointer to string to compare with str1
 *
 * Return: an int to determine string similarities
 */

int _strcmp(const char *str1, const char *str2)
{
	if (!str1 || !str2)
		return (-1);

	if (!str1 && !str2)
		return (0);

	while (*str1 && *str2 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

/**
 * _putchar - a function that writes the character c to stdout
 * @c: the character to print
 *
 * Return: On success 1, on error, -1 is returned, and errno is set
 * appropriately
 */

int _putchar(char c)
{
	return (write(STDIN_FILENO, &c, 1));
}

/**
 * _puts - a function that prints a string to stdout
 * @str: pointer to the string to be printed
 *
 * Return: string to stdout
 */

void _puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		_putchar(str[i]);
	_putchar('\n');
}

/**
 * _strchr - locates a character in a given string
 * @s: the string to check
 * @c: the character to check
 *
 * Return: pointer to the first occurence of the character
 */

char *_strchr(char *s, char c)
{
	for (; *s; s++)
	{
		if (*s != c)
			continue;
		else
			return (s);
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

/**
 * _strtok - a function that breaks a string into series of tokens using a
 * delim
 * @str: string to break down
 * @delim: delimiter passed as argument
 *
 * Return: pointer to the first broken word
 */

char *_strtok(char *str, char *delim)
{
	static char *current;
	char *start;

	if (str)
		current = str;

	if (!current || *current == '\0')
		return (NULL);

	start = current;
	while (*current != '\0' && _strchr(delim, *current) == NULL)
		current++;
	if (*current != '\0')
		*current++ = '\0';
	return (start);
}

