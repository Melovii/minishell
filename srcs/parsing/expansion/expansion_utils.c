#include "minishell.h"
#include "../libft/libft.h"

static char	*parse_braced_var_name(t_shell *shell, char *s, int *i);
static char	*parse_simple_var_name(t_shell *shell, char *s, int *i);

char	*load_var_value(t_shell *shell, char *name)
{
	char	*exit_value_str;
	char	*default_value;

	if (!name)
		return (NULL);
	if (name[0] == '?' && name[1] == '\0')
	{
		exit_value_str = ft_itoa(shell->exit_flag);
		if (!exit_value_str)
		{
			free(name);
			shut_program(shell, true, EX_KO);
		}
		return (exit_value_str);
	}
	if (get_env_value(shell->env, name) == NULL)
		return (NULL);
	default_value = ft_strdup(get_env_value(shell->env, name));
	if (!default_value)
	{
		free(name);
		shut_program(shell, true, EX_KO);
	}
	return (default_value);
}
 
char	*parse_var_name(t_shell *shell, char *input, int *i)
{
	if (input[*i] == '{')
		return (parse_braced_var_name(shell, input, i));
	return (parse_simple_var_name(shell, input, i));
}

static char	*parse_braced_var_name(t_shell *shell, char *input, int *i)
{
	int		start;
	int		len;
	char	*name;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '}')
    {
		(*i)++;
    }
	len = (*i) - start;
	name = ft_substr(input, start, len);
	if (!name)
    {
		shut_program(shell, true, EX_KO);
    }
	if (input[*i] == '}')
    {
		(*i)++;
    }
	return (name);
}

static char	*parse_simple_var_name(t_shell *shell, char *input, int *i)
{
	int		start;
	int		len;
	char	*name;

	start = *i;
	if (input[*i] == '?') // * special case for $?
	{
		(*i)++;
		len = 1;
	}
	else if (ft_isalpha((int)input[*i]) || input[*i] == '_') // * valid first char
	{
		(*i)++;
		while (ft_isalnum((int)input[*i]) || input[*i] == '_')
			(*i)++;
		len = (*i) - start;
	}
	else // * invalid var name, no expansion
	{
		return (NULL);
	}
	name = ft_substr(input, start, len);
	if (!name)
		shut_program(shell, true, EX_KO);
	return (name);
}



