#include "simple_shell.h"

int main(void)
{
	const char *text;
	int c = 'a';
	char *result;

	text = "Hello, World!";
	result = _strchr(text, c);

	if (result != NULL)
		printf("Character '%c' found at position: %s\n", c, result);
	else
		printf("Character '%c' not found\n", c);
	return (0);
}
