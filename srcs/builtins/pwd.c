#include "minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		if (errno == ENOMEM)
			shut_program(shell, "minishell: malloc failed in pwd", 1);
		else
		{
			perror("minishell: pwd");
			return (1);
		}
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}

