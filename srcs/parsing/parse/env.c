#include "minishell.h"

// * Initializes the environment variables by creating nodes for each key-value pair
void	init_env(t_shell *shell, char **envp)
{
	int		i;
	t_env	*new_node;

	shell->og_env = envp;
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

// * Finds an environment variable node by its key
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

// * Returns the value associated with an environment variable given its key
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

// * Frees the entire linked list of environment nodes
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

// * Frees a single environment node
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
