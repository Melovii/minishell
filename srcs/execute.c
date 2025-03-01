#include "minishell.h"

// * Execute commands:
// If it's a built-in command → execute it inside Minishell
// If it's an external command → create a child process using fork() and execve()

void	handle_builtin(char **args)
{
	// TODO: Handle the following builtin commands
	// echo 	with option -n
	// cd 		with cd with only a relative or absolute path
	// pwd 		with no options
	// export 	with no options
	// unset 	with no options
	// env 		with no options or arguments
	// exit 	with no options
}

t_bool	execute_cmd(char **args)
{
	t_command	cmd;

	// TODO:
	// Fork a new process and handle errors
	// Execute the command in the child process using execvp()
	// Wait for the child in the parent process
	// Handle errors for fork() and execvp()

	if (cmd.is_builtin)
		handle_builtin(args);
	else
		execute_external(args);
}
