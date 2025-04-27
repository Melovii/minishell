#include "minishell.h"
#include "../libft/libft.h"

static char	*parse_braced_var_name(t_shell *shell, char *s, int *i);
static char	*parse_simple_var_name(t_shell *shell, char *s, int *i);

char	*load_var_value(t_shell *shell, char *name)
{
	if (name[0] == '?' && name[1] == '\0')
		return (ft_itoa(shell->exit_flag));
	return (get_env_value(shell->env, name));
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
	while (ft_isalnum((int)input[*i]) || input[*i] == '_' || input[*i] == '?')
    {
		(*i)++;
    }
	len = (*i) - start;
	name = ft_substr(input, start, len);
	if (!name)
    {
		shut_program(shell, true, EX_KO);
    }
	return (name);
}



