
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
	if (exit_code == 127)
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
	else if (exit_code == 126)
	{
		print_open_error(cmd);
	}
}

// * Prints error message based on the filename and error type (ENOENT, EACCES, etc.)
void print_open_error(char *filename)
{
    if (errno == ENOENT)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(filename, 2);
        ft_putendl_fd(": No such file or directory", 2);
    }
    else if (errno == EACCES)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(filename, 2);
        ft_putendl_fd(": Permission denied", 2);
    }
    else
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(filename, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
    }
}

// * Prints a warning message when encountering an EOF in a heredoc
void	eof_msg(t_shell *shell, char *delimiter)
{
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putnbr_fd((int)shell->number_of_prompts, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
