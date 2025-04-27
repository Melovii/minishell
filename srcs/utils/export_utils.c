#include "minishell.h"
#include "../libft/libft.h"

static void	fill_env_key_value(t_shell *shell, t_env *new, char *arg);
static void	handle_env_alloc_failure(t_shell *shell, t_env *node);
static void	add_env_node_with_data(t_shell *shell, char *key, char *value);

void	add_or_update_env(t_shell *shell, char *key, char *value)
{
	t_env	*node;

	node = find_env_node(shell->env, key);
	if (node)
	{
		if (value)
		{
			free(node->value);
			node->value = ft_strdup(value);
			if (!node->value)
				shut_program(shell, "Allocation failed in add_or_update_env", 1);
		}
	}
	else
		add_env_node_with_data(shell, key, value);
}

static void	add_env_node_with_data(t_shell *shell, char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		shut_program(shell, "Allocation failed in add_env_node_with_data", 1);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		shut_program(shell, "Allocation failed for key", 1);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->key);
			free(new);
			shut_program(shell, "Allocation failed for value", 1);
		}
	}
	add_env_node(&shell->env, new);
}

t_env	*parse_export_argument(t_shell *shell, char *arg)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		shut_program(shell, "Alloc error in parse_export_argument", 1);
	fill_env_key_value(shell, new, arg);
	return (new);
}

static void	fill_env_key_value(t_shell *shell, t_env *new, char *arg)
{
	char	*equal_sign;
	int		key_len;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key_len = equal_sign - arg;
		new->key = ft_substr(arg, 0, key_len);
		if (!new->key)
            handle_env_alloc_failure(shell, new);
		new->value = ft_strdup(equal_sign + 1);
		if (!new->value)
            handle_env_alloc_failure(shell, new);
	}
	else
	{
		new->key = ft_strdup(arg);
		if (!new->key)
            handle_env_alloc_failure(shell, new);
		new->value = NULL;
	}
}

static void	handle_env_alloc_failure(t_shell *shell, t_env *node)
{
	if (node)
	{
		if (node->key)
			free(node->key);
		if (node->value)
			free(node->value);
	}
	free(node);
	shut_program(shell, "Allocation failed in fill_env_key_value", 1);
}
