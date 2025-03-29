#include "minishell.h"

int	measure_expanded_length(const char *s, t_shell *shell)
{
	int	i;
	int	len;
	char	var_name[256];
	char	*value;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] && s[i] == '{')
			{
				extract_braced_var_name(s, &i, var_name);
				value = get_env_value(shell->env, var_name);
				if (value)
					len += ft_strlen(value);
			}
			else if (s[i] && is_var_char(s[i]))
			{
				extract_var_name(s, &i, var_name);
				value = get_env_value(shell->env, var_name);
				if (value)
					len += ft_strlen(value);
			}
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

void	extract_braced_var_name(const char *s, int *i, char *var_name)
{
	int	k;

	k = 0;
	(*i)++; /* '{' karakterini atla */
	while (s[*i] && s[*i] != '}' && k < 255)
	{
		var_name[k++] = s[*i];
		(*i)++;
	}
	if (s[*i] == '}')
		(*i)++;
	var_name[k] = '\0';
}

void	extract_var_name(const char *s, int *i, char *var_name)
{
	int	k;

	k = 0;
	while (s[*i] && is_var_char(s[*i]) && k < 255)
	{
		var_name[k++] = s[*i];
		(*i)++;
	}
	var_name[k] = '\0';
}

int	is_var_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}
