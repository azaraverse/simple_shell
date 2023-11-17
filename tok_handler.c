#include "a_shell.h"

/**
 * _strspn - a function that gets or counts the length of a prefix substring
 * @s: segment consisting of bytes
 * @accept: bytes in the segment to accept
 *
 * Return: accepted bytes
 */

size_t _strspn(char *s, const char *accept)
{
	int z= 0;
	int x, y;

	for (x = 0; s[x] != '\0'; x++)
	{
		if (s[x] != ' ')
		{
			for (y = 0; accept[y] != '\0'; y++)
			{
				if (s[x] == accept[y])
					z++;
			}
		}
		else
			return (z);
	}
	return (z);
}

/**
 * _strtokMul - a function that breals a string into series of tokens using
 * mulitple delimiters
 * @str: string to break down
 * @delim: string containing delimiters
 * @savePtr: pointer to a char pointer to store the state between calls
 *
 * Return: pointer to the next token, or NULL if no more tokens are found
 */

char *_strtokMul(char *str, const char *delim, char **savePtr)
{
	char *token_start, *token_end;

	if (!str && !*savePtr)
		return (NULL);

	if (!str)
		str = *savePtr;

	token_start = str + _strcspn(str, delim);
	if (*token_start == '\0')
	{
		*savePtr = NULL;
		return (NULL);
	}

	token_end = token_start + _strspn(token_start, delim);
	if (*token_end == '\0')
		*savePtr = NULL;
	else
	{
		*token_end = '\0';
		*savePtr = token_end + 1;
	}
	return (token_start);
}
