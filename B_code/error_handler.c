#include "a_shell.h"

/**
 * _itoa - a function that converts an integer to string
 * @num: integer to convert
 * @s: buffer to store resulting str
 * @base: integer base for conversion
 *
 * Return: converted string
 */

char *_itoa(int num, char *s, int base)
{
	int i = 0, isNeg = 0, remainder, start, end;
	char temp;

	if (base < 2 || base > 36)
		return (NULL);
	/* handle negative numbers */
	if (num < 0 && base == 10)
	{
		isNeg = 1;
		num = -num;
	}

	/* convert number to a str in reverse order */
	while (num != 0)
	{
		remainder = num % base;
		s[i++] = (remainder < 10) ? (char)(remainder + '0') :
			(char)(remainder - 10 + 'a');
		num /= base;
	}
	if (isNeg && base == 10)
		s[i++] = '-';
	s[i] = '\0';

	/* reverse the string */
	start = 0;
	end = i - 1;
	while (start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
	return (s);
}

/**
 * fork_error - a function that handles fork errors
 * @cmdCounter: error return value
 */

void fork_error(int cmdCounter)
{
	char err_message[1024], cmdStr[12];

	_strcpy(err_message, _getenv("0"));
	_strcat(err_message, ": ");
	_itoa(cmdCounter, cmdStr, 10);
	_strcat(err_message, cmdStr);
	_strcat(err_message, ": fork failed\n");

	write(STDERR_FILENO, err_message, _strlen(err_message));
	exit(EXIT_FAILURE);
}

/**
 * cmd_error - a function that handles command not found errors
 * @cmdCounter: int return value
 * @name: program name
 * @cmd: command name
 */

void cmd_error(int cmdCounter, char *name, char *cmd)
{
	char err_message[1024], cmdStr[12];

	_strcpy(err_message, name);
	_strcat(err_message, ": ");
	_itoa(cmdCounter, cmdStr, 10);
	_strcat(err_message, cmdStr);
	_strcat(err_message, ": ");
	_strcat(err_message, cmd);
	_strcat(err_message, ": not found\n");

	write(STDERR_FILENO, err_message, _strlen(err_message));
}

/**
 * execve_error - a function that handles execve failed errors
 * @current_cmd: int return value
 * @name: program name
 * @cmd: command name
 */

void execve_error(int current_cmd, char *name, char *cmd)
{
	char err_message[1024], cmdStr[12];

	_strcpy(err_message, name);
	_strcat(err_message, ": ");
	_itoa(current_cmd, cmdStr, 10);
	_strcat(err_message, cmdStr);
	_strcat(err_message, ": ");
	_strcat(err_message, cmd);
	_strcat(err_message, ": execution failed\n");

	write(STDERR_FILENO, err_message, _strlen(err_message));
}
