#include "minishell.h"

static bool	check_flag(char *args);

// * Function to echo arguments (with -n flag)
int	ft_echo(char **args)
{
	int		i;
	bool	is_newline;

	i = 1;
	is_newline = false;
	while (args[i] && check_flag(args[i]))
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

// Returns true if the argument is a valid -n flag (e.g., -n, -nn, -nnn...), false otherwise
static bool	check_flag(char *args)
{
	int	i;

	if (!(args && args[0] == '-' && args[1] == 'n'))
	{
		return (false);
	}
	i = 2;
	while (args[i])
	{
		if (args[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}
