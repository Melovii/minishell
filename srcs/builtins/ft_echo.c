#include "minishell.h"

// * Function to echo arguments (with -n flag)
int	ft_echo(char **args)
{
	int	i;
	bool	is_newline;

	i = 1;
	is_newline = false;
	while (args[i] && are_strs_equal("-n", args[i]))
	{
		is_newline = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!is_newline)
		ft_putendl_fd("", 1);
	return (EX_OK);
}
