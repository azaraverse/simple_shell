#include "a_shell.h"

/**
 * _strcmp - a function that compares two strings
 * @str1: pointer to string to compare
 * @str2: pointer to string to compare with str1
 *
 * Return: an int to determine string similarities
 */

int _strcmp(char *str1, char *str2)
{
	while (((*str1 != '\0') && (*str2 != '\0')) && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 - *str2);
}
