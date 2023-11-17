#include "a_shell.h"

int global_status = 0;
/**
 * _exitt - a function that handles the 'exit' built-in command
 * @argv: double pointer to a pointer holding built-in command 'exit'
 */

void _exitt(char **argv)
{
	int exit_status;

	if (argv[1])
	{
		exit_status = atoi(argv[1]);
		if (exit_status == 0 || exit_status == 2)
			global_status = exit_status;
		else
			global_status = 2;
	}
	exit(global_status);
}

/**
 * _printenv - a function that prints the current environment to stdout
 */

void _printenv(void)
{
	unsigned int i;
	char *shell, *args[4];

	if (!_isatty(STDIN_FILENO))
	{
		shell = "/bin/sh";
		args[0] = shell;
		args[1] = "-c";
		args[2] = "env";
		args[3] = NULL;
		execve(shell, args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (environ[i])
	{
		_puts(environ[i]);
		i++;
	}
}

/**
 * init_builtin - a function that initialises the array of builtin commands
 * Return: functions to execute built-in commands
 */

const built_in *init_builtin(void)
{
	static const built_in builtIns[] = {
		{"exit", _exitt},
		{"env", _printenv},
		{NULL, NULL}
	};
	return (builtIns);
}

/**
 * is_builtin - a function that checks if a command is a built-in command
 * @builtIns: pointer to an array of built-in commands
 * @cmd: pointer to a string of command to compare against builtIns
 *
 * Return: 1 if command is a built-in, 0 if command is not a built-in
 */

int is_builtin(const built_in *builtIns, char *cmd)
{
	int i;

	for (i = 0; builtIns[i].name; i++)
	{
		if (_strcmp(cmd, builtIns[i].name) == 0)
			return (1);
	}
	return (0);
}

/**
 * exec_cmd - a function that executes a command either a built-in or external
 * command
 * @builtIns: pointer to an array of built-in commands
 * @argv: command passed as argument
 */

void exec_cmd(const built_in *builtIns, char **argv)
{
	int i, exit_status;

	if (!argv || !argv[0])
		return;

	if (is_builtin(builtIns, argv[0]))
	{
		for (i = 0; builtIns[i].name; i++)
		{
			if (_strcmp(argv[0], builtIns[i].name) == 0)
			{
				builtIns[i].handler();
				return;
			}
		}
	}
	else
	{
		exit_status = exec(argv);
		if (exit_status != -1)
		{
			global_status = exit_status;
			return;
		}
	}
	global_status = 1;
}
