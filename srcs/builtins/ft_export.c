#include "minishell.h"

static bool	process_export_argument(t_shell *shell, char *arg);
static void	print_invalid_identifier(char *arg);

// * Main function for handling the export command, processes each argument for export
int	ft_export(t_shell *shell, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!args[1])
	{
		print_export(shell);
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

// * Processes a single export argument, validating and adding/updating the environment variable
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

// * Prints an error message when an invalid export identifier is encountered
static void	print_invalid_identifier(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

// * Checks if a given key is a valid environment variable identifier
bool	is_valid_identifier(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (false);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
