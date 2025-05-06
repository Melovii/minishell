
#include "minishell.h"

// * Prints error message when the command is a directory
void	print_dir_error(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
}

// * Prints error message for path-related issues (no file or command not found)
void	path_error_msg(char *cmd, int exit_code, bool is_direct)
{
	if (exit_code == CMD_NOT_FOUND)
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
	else if (exit_code == EXEC_NO_PERM)
	{
		print_open_error(cmd);
	}
}

// * Prints error message based on the filename and error type (ENOENT, EACCES, etc.)
void print_open_error(char *filename)
{
    if (errno == ENOENT)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(filename, STDERR_FILENO);
        ft_putendl_fd(": No such file or directory", STDERR_FILENO);
    }
    else if (errno == EACCES)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(filename, STDERR_FILENO);
        ft_putendl_fd(": Permission denied", STDERR_FILENO);
    }
    else
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(filename, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putendl_fd(strerror(errno), STDERR_FILENO);
    }
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
