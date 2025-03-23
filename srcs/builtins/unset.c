#include "minishell.h"

static t_env	*find_removed_node(char *delimeter, t_env *env_list);
static void		remove_env_node(t_env *removed_env, t_env **env_list);

// * Function to unset environment variables
int	ft_unset(t_shell *shell, char **args)
{
	int		i;
	t_env	removed_env;
	t_env	*env_list;
	char	*delimiter;

	if (!args[1])
		return (EX_OK);
	env_list = shell->env;
	i = 1;
	while (args[i])
	{
		delimiter = args[i];
		remove_env_node(find_removed_node(delimiter, env_list), &env_list);
		i++;
	}
	return (EX_OK);
}

static void	remove_env_node(t_env *removed_env, t_env **env_list)
{
	t_env	*tmp_list;
	t_env	*prev;

	if (!removed_env || !env_list || !*env_list)
		return ;
	tmp_list = *env_list;
	prev = NULL;
	while (tmp_list)
	{
		if (are_strs_equal(tmp_list->key, removed_env->key))
		{
			if (prev == NULL)
				*env_list = tmp_list->next;
			else
				prev->next = tmp_list->next;
			free(tmp_list->key);
			free(tmp_list->value);
			free(tmp_list);
			return ;
		}
		prev = tmp_list;
		tmp_list = tmp_list->next;
	}
}

static t_env	*find_removed_node(char *delimeter, t_env *env_list)
{
	while (env_list)
	{
		if (are_strs_equal(env_list->key, delimeter))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
