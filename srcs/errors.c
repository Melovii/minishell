#include "../libft/libft.h"
#include "minishell.h"

// * Function to print error message for if command is a directory
void	print_dir_error(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
}

void	path_error_msg(char *cmd, int exit_code, bool is_direct)
{
	if (exit_code == 127)
	{
		if (is_direct)
			ft_putstr_fd("minishell: no such file or directory: ", STDERR_FILENO);
		else
			ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	}
	else if (exit_code == 126)
	{
		ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
	}
	ft_putendl_fd(cmd, STDERR_FILENO);
}

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

void	eof_msg(t_shell *shell, char *delimiter)
{
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putnbr_fd((int)shell->number_of_prompts, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
