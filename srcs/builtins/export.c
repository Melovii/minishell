#include "minishell.h"

static bool		is_valid_identifier(char *arg);
static void		invalid_env(int *status, t_env *node);
static t_env	*parse_export_argument(char *arg);
static void		add_or_update_env(t_env **env, char *key, char *value);

// * Function to export environment variables
// ! Error handling does not exist
int	ft_export(t_shell *shell, char **args)
{
	int		i;
	int		status;
	t_env	*node;

	i = 1;
	status = 0;
	if (!args[1])
		return (EX_OK);
	while (args[i])
	{
		node = parse_export_argument(args[i]);
		if (!node->value)
		{
			free_env(node);
			i++;
			continue ;
		}
		if (!is_valid_identifier(node->key))
			invalid_env(&status, node);
		else
			add_or_update_env(&shell->env, node->key, node->value);
		free_env(node);
		i++;
	}
	return (status);
}
// ! error handling does not exist
// * purpose: if there is no env add new one or already exist update its value
static void	add_or_update_env(t_env **env, char *key, char *value)
{
	t_env	*node;
	t_env	*new;

	node = find_env_node(*env, key);
	if (node)
	{
		if (value)
			node->value = ft_strdup(value);
	}
	else
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			handle_error("allocation", EX_KO); // !	check later
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		if (!(new->key) || !(new->value))
		{
			free_env(new);
			handle_error("allocation", EX_KO); // !	check later
		}
		add_env_node(env, new);
	}
}

// ! error handling does not exist
// * purpose: parsing the key and its value
static t_env	*parse_export_argument(char *arg)
{
	t_env	*new;
	char	*equal_sign;
	int		key_len;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key_len = equal_sign - arg;
		new->key = ft_substr(arg, 0, key_len);
		new->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		new->key = ft_strdup(arg);
		new->value = NULL;
	}
	return (new);
}
// * purpose:  Checking whether key value is valid or not.
static bool	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (false);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

// * purpose: execute commands after the invalid key syntax
static void	invalid_env(int *status, t_env *node)
{
	if (*status == 0)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd("not an identifier: ", 2);
		ft_putendl_fd(node->key, 2);
	}
	*status = 1;
}
