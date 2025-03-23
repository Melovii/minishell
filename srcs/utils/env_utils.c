#include "minishell.h"

// * Create a new environment variable node
static t_env	*create_env_node(char *env_var)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(env_var, '=');
	if (!equal_sign)
	{
		new_node->key = ft_strdup(env_var);
		new_node->value = NULL;
	}
	else
	{
		new_node->key = ft_substr(env_var, 0, equal_sign - env_var);
		new_node->value = ft_strdup(equal_sign + 1);
	}
	new_node->next = NULL;
	return (new_node);
}

// * Add node to the environment linked list
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

t_env	*find_env_node(t_env *list, char *key)
{
	while (list)
	{
		if (are_strs_equal(list -> key, key))
			return (list);
		list = list -> next;
	}
	return (NULL);
}

void	free_env(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

// * Initialize environment variables from envp
void	init_env(t_shell *shell, char **envp)
{
	int		i;
	t_env	*new_node;

	if (!shell || !envp)
		return ;
	shell->env = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		add_env_node(&shell->env, new_node);
		i++;
	}
}
