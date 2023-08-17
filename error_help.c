#include "simple_shell.h"

/**
 * command_error - print a "command not found" error message and exit.
 * @cmd: the command that was not found.
 */

void command_error(const char *cmd)
{
	const char *error_meassage = "simple_shell: Error: Command '";
	size_t error_message_length = _strlen(error_message);

	/** write the error message to standard error **/
	write(STDERR_FILENO, error_message, error_message_length);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, "' not found\n", 12);

}

/**
 * fork_error - print a "fork failed" error message and exit.
 */

void fork_error(void)
{
	const char *error_message = "simple_shell: Error: Fork failed\n";
	const size_t error_message_length = _strlen(error_message);

	/** write the error message to standard error**/
	write(STDERR_FILENO, error_message, error_message_length);

}
