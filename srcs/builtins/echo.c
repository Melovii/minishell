#include "minishell.h"

// * Function to echo arguments (with -n flag)
int	ft_echo(char **args)
{
	int	i;
	
	if (!args[1])
	{
		ft_putendl_fd("", 1);
		return (EX_OK);
	}
	else
	{
		i = 1;
		if (are_strs_equal("-n", args[1]))
			i++;
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
		if (!are_strs_equal("-n", args[1]))
			ft_putendl_fd("", 1);
		return (0);
	}
}
