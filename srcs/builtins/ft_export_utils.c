#include "minishell.h"

static char **sort_keys(t_shell *shell);
static int	count_key_number(t_env *env);
static void	sort_env_array(char **arr);
static int	ft_strcmp(const char *s1, const char *s2);

void print_export(t_shell *shell)
{
	char **sorted_keys;
	int	i;

	sorted_keys = sort_keys(shell);
	i = 0;
	while (sorted_keys[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(sorted_keys[i], 1);
		if (get_env_value(shell->env, sorted_keys[i]) != NULL)
		{
			ft_putstr_fd("= \"", 1);
			ft_putstr_fd(get_env_value(shell->env, sorted_keys[i]), 1);
			ft_putendl_fd("\"", 1);
		}
		i++;
	}
	free(sorted_keys);
}

static char **sort_keys(t_shell *shell)
{
	t_env	*env;
	char	**keys_arr;
	int		i;

	keys_arr = ft_calloc(count_key_number(shell->env) + 1, sizeof(char *));
	if (!keys_arr)
		shut_program(shell, true, 1);
	i = 0;
	env = shell->env;
	while (env)
	{
		keys_arr[i] = env->key;
		i++;
		env = env->next;
	}
	sort_env_array(keys_arr);
	return (keys_arr);
}

static void	sort_env_array(char **arr)
{
	int		i;
	int		sorted;
	char	*tmp;

	if (!arr)
		return;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (arr[i] && arr[i + 1])
		{
			if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}


static int	count_key_number(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env -> next;
	}
	return (count);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j] && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

