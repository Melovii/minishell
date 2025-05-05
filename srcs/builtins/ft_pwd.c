#include "minishell.h"

// * Prints the current working directory
int	ft_pwd(t_shell *shell)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		if (errno == ENOMEM)
			shut_program(shell, true, 1);
		else
		{
			perror("minishell: pwd");
			return (1);
		}
	}
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}

