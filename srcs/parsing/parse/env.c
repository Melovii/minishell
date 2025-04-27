#include "minishell.h"
#include "../libft/libft.h"
#include "stdlib.h"

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
		new_node = create_env_node(shell, envp[i]);
		add_env_node(&shell->env, new_node);
		i++;
	}
}

t_env	*find_env_node(t_env *env, char *key)
{
	while (env)
	{
		if (are_strs_equal(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char    *get_env_value(t_env *env, char *key)
{
    while (env)
    {
        if (are_strs_equal(env->key, key))
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

void	free_env_list(t_env *env)
{
	t_env	*curr;
	t_env	*next;

	curr = env;
	while (curr)
	{
		next = curr->next;
		if (curr->key)
			free(curr->key);
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = next;
	}
}

void	free_env(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}
