#include "minishell.h"

static void	add_env_node_with_data(t_shell *shell, char *key, char *value);

// * Adds or updates an environment variable in the shell's environment
void	add_or_update_env(t_shell *shell, char *key, char *value)
{
	t_env	*node;
	char	*temp;

	node = find_env_node(shell->env, key);
	if (node)
	{
		if (value)
		{
			temp = node->value;
			node->value = ft_strdup(value);
			if (!node->value)
			{
				shut_program(shell, true, 1);
			}
			free(temp);
		}
	}
	else
	{
		add_env_node_with_data(shell, key, value);
	}
}

// * Helper function to add a new environment node with the specified key and value
static void	add_env_node_with_data(t_shell *shell, char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		shut_program(shell, true, 1);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		shut_program(shell, true, 1);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->key);
			free(new);
			shut_program(shell, true, 1);
		}
	}
	add_env_node(&shell->env, new);
}

// * Parses an export argument to create a new environment variable node
t_env	*parse_export_argument(t_shell *shell, char *arg)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
	{
		shut_program(shell, true, 1);
	}
	set_env_key_value(shell, new, arg);
	return (new);
}
