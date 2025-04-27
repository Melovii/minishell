#include "../libft/libft.h"
#include "minishell.h"

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
