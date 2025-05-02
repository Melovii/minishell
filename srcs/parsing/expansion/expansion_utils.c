#include "minishell.h"

static int	get_special_case_len(t_shell *shell, char *s, int *i);
static int get_default_len(t_shell *shell, char *s, int *i);

int handle_env_var_len(t_shell *shell, char *s, int *i)
{
	int len;
	int j;

	j = *i + 1;
	if (s[j] == '?')
		return (get_special_case_len(shell, s, i));
	if (ft_isalpha(s[j]) || s[j] == '_')
		return (get_default_len(shell, s, i));
	while (s[j] && is_quote(s[j]) == false)
	{
		if (s[j] == '$')
			break ;
		j++;
	}
	len = j - (*i) + 1;
	*i = j;
	return (len);
}

static int get_default_len(t_shell *shell, char *s, int *i)
{
	int len;
	char *var;

	len = 0;
	var = s + *i + 1;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
	{
		len++;
		(*i)++;
	}
	var = ft_substr(var, 0, len);
	if (!var)
		shut_program(shell, true, EX_KO);
	len = ft_strlen(get_env_value(shell->env, var));
	free(var);
	return (len);
}


static int	get_special_case_len(t_shell *shell, char *s, int *i)
{
	int len;
	char *var;

	var = ft_itoa(shell->exit_flag);
	if (!var)
		shut_program(shell, true, EX_KO);
	len = ft_strlen(var);
	free(var);
	(*i) += 2;
	return (len);
}
