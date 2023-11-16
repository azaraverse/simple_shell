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
