#include "minishell.h"

static int	calc_extended_len(t_shell *shell, int *i, int mode);

void	fill_new_value(char *src, char *dst, int *j)
{
	int	k;

	k = 0;
	while (src[k])
	{
		dst[*j] = src[k];
		(*j)++;
		k++;
	}
}

int	measure_expanded_length(const char *str, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] && str[i] == '{')
				len += calc_extended_len(shell, &i, 2);
			else if (str[i] && is_var_char(str[i]))
				len += calc_extended_len(shell, &i, 1);
			else
				len++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static int	calc_extended_len(t_shell *shell, int *i, int mode)
{
	int		len;
	char	var_name[256];
	char	*value;

	len = 0;
	if (mode == 1)
	{
		extract_var_name(shell->token->value, i, var_name);
		value = get_env_value(shell->env, var_name);
		if (value)
			len += ft_strlen(value);
	}
	else if (mode == 2)
	{
		extract_braced_var_name(shell->token->value, i, var_name);
		value = get_env_value(shell->env, var_name);
		if (value)
			len += ft_strlen(value);
	}
	return (len);
}
