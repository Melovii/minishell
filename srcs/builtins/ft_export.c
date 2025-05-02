#include "minishell.h"
#include "../libft/libft.h"

static bool	process_export_argument(t_shell *shell, char *arg);
static void	print_invalid_identifier(char *arg);
static int	is_valid_identifier(char *key);

int	ft_export(t_shell *shell, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!args[1])
	{
		ft_env(shell, args, true);
		return (0);
	}
	while (args[i])
	{
		if (!process_export_argument(shell, args[i]))
			status = 1;
		i++;
	}
	return (status);
}

static bool	process_export_argument(t_shell *shell, char *arg)
{
	t_env	*node;

	node = parse_export_argument(shell, arg);
	if (!node || !is_valid_identifier(node->key))
	{
		print_invalid_identifier(arg);
		free_env(node);
		return (false);
	}
	add_or_update_env(shell, node->key, node->value);
	free_env(node);
	return (true);
}

static void	print_invalid_identifier(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

static int	is_valid_identifier(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
