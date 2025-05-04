#include "minishell.h"

static int	get_special_case_len(t_shell *shell, int *i);
static int get_default_len(t_shell *shell, char *s, int *i);

// * Copies characters from src to dst starting at index j
void	ft_strcpy_to(char *dst, char *src, int *j)
{
	int i = 0;
	while (src[i])
		dst[(*j)++] = src[i++];
}

// * Calculates the length of an environment variable or special case and updates the index
int	handle_env_var_len(t_shell *shell, char *str, int *i, bool is_in_q)
{
	int j;

	j = *i + 1;

	if (str[j] == '?')
		return (get_special_case_len(shell, i));
	if (ft_isalpha(str[j]) || str[j] == '_')
		return (get_default_len(shell, str, i));
	if (ft_isdigit(str[j]))
	{
		*i += 2;
		return (0);
	}
	if (is_quote(str[j]) && !is_in_q)
	{
		*i += 1;
		return (0);
	}
	if (str[j])
	{
		*i += 2;
		return (2);
	}
	*i += 1;
	return (1);
}

// * Gets the length of a normal environment variable's value and updates the index
static int	get_default_len(t_shell *shell, char *str, int *i)
{
	int		start;
	int		end;
	char	*var;
	char	*val;
	int		len;

	start = *i + 1;
	end = start;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	var = ft_substr(str, start, end - start);
	if (!var)
		shut_program(shell, true, EX_KO);
	val = get_env_value(shell->env, var);
	if (val)
		len = ft_strlen(val);
	else
		len = 0;
	free(var);
	*i = end;
	return (len);
}

// * Returns the length of the exit code as a string and updates the index
static int	get_special_case_len(t_shell *shell, int *i)
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
