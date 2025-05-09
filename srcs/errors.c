
#include "minishell.h"

static void	print_open_err_msg(char *filename, char *message);

// * Prints error message when the command is a directory
void	print_dir_error(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
}

// * Prints error message for path-related issues (no file or command not found)
void	path_error_msg(t_shell *shell, char *cmd, int exit_code, bool is_direct)
{
	if (exit_code == NOT_FOUND)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		if (is_direct)
		{
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}
	}
	else if (exit_code == NO_PERM)
	{
		print_open_error(shell, cmd);
	}
}

// * Prints error message based on the filename and errno (ENOENT, EACCES, ENOMEM, etc.)
void	print_open_error(t_shell *shell, char *filename)
{
	if (errno == ENOENT)
		print_open_err_msg(filename, ": No such file or directory");
	else if (errno == EACCES)
		print_open_err_msg(filename, ": Permission denied");
	else if (errno == ENOMEM)
	{
		shut_program(shell, true, EX_KO);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
}

// * Prints a formatted error message to STDERR with a fixed prefix
static void	print_open_err_msg(char *filename, char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}

// * Prints a warning message when encountering an EOF in a heredoc
void	eof_msg(t_shell *shell, char *delimiter)
{
	ft_putstr_fd("warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd((int)shell->number_of_prompts, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}
