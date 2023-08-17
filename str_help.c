#include "simple_shell.h"

/**
 * _strchr - function returns a pointer to the first occurence of the character
 *c in the string s
 * @s: pointer to the string to iterate
 * @c: character to iterate for in the string
 *
 * Return: a pointer to the matched character or NULL if the character is not
 *found
 */

char *_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (char *)s; /* cast to char * to match strchr */
		s++;
	}
	return (NULL);
}

/**
 * _strlen - returns the length of a string.
 * @string - char to check.
 *
 * Return: length of string.
 */

unsigned int _strlen(const char *string)
{
	unsigned int length = 0;

	while (string[length] != '\0')
	{
		length++;
	}

	return (lenght);

}
