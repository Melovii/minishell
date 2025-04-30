#include "minishell.h"
#include "../libft/libft.h"

static void	set_key_no_value(t_shell *shell, t_env *node, char *env_var);
static void	set_key_value_pair(t_shell *shell, t_env *node, char *env_var, char *equal_sign);

void	add_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*current;

	if (!new_node)
		return ;
	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_env	*create_env_node(t_shell *shell, char *env_var)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
    if (!new_node)
    {
        shut_program(shell, true, EX_KO);
    }
	set_env_key_value(shell, new_node, env_var);
	return (new_node);
}

void	set_env_key_value(t_shell *shell, t_env *node, char *env_var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_var, '=');
	if (!equal_sign)
		set_key_no_value(shell, node, env_var);
	else
		set_key_value_pair(shell, node, env_var, equal_sign);
}

static void	set_key_no_value(t_shell *shell, t_env *node, char *env_var)
{
	node->key = ft_strdup(env_var);
	if (!node->key)
	{
		free_env(node);
		shut_program(shell, true, EX_KO);
	}
	node->value = NULL;
}


static void	set_key_value_pair(t_shell *shell, t_env *node, char *env_var, char *equal_sign)
{
	node->key = ft_substr(env_var, 0, equal_sign - env_var);
	if (!node->key)
	{
		free_env(node);
		shut_program(shell, true, EX_KO);
	}
	node->value = ft_strdup(equal_sign + 1);
	if (!node->value)
	{
		free_env(node);
		shut_program(shell, true, EX_KO);
	}
}

