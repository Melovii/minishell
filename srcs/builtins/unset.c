#include "minishell.h"
#include "../libft/libft.h"

static void	remove_env_node(t_env **env_list, char *key);
static bool	is_valid_identifier(char *str);

int	ft_unset(t_shell *shell, char **args)
{
	int		i;

	if (!args[1])
		return (EX_OK);
	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			remove_env_node(&shell->env, args[i]);
		i++;
	}
	return (EX_OK);
}

static void	remove_env_node(t_env **env_list, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env_list;
	prev = NULL;
	while (tmp)
	{
		if (are_strs_equal(tmp->key, key))
		{
			if (prev == NULL)
				*env_list = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
