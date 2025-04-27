#include "minishell.h"

static int	handle_env_var(t_shell *shell, char *s, int *i);
static int	measure_without_q(t_shell *shell, char *s, int *i);
static int	measure_sq(char *s, int *i);
static int	measure_dq(t_shell *shell, char *s, int *i);

int measure_len(t_shell *shell, char *s)
{
    int len;
    int i;

    len = 0;
    i = 0;
    while (s[i]) 
    {
        if (s[i] == '\'') 
        {
            len += measure_sq(s, &i);
        }
        else if (s[i] == '"')
        {
            len += measure_dq(s, &i, shell);
        }
        else
        {
            len += measure_without_q(s, &i, shell);
        }
    }
    return (len);
}

static int	measure_sq(char *s, int *i)
{
	int	len;

	len = 0;
	(*i)++;
	while (s[*i] && s[*i] != '\'')
	{
		len++;
		(*i)++;
	}
	if (s[*i] == '\'')
		(*i)++;
	return (len);
}


static int	measure_dq(t_shell *shell, char *s, int *i)
{
	int	len;

	len = 0;
	(*i)++;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$' && s[*i + 1])
		{
			(*i)++;
			len += handle_env_var(shell, s, i);
		}
		else
		{
			len++;
			(*i)++;
		}
	}
	if (s[*i] == '"')
		(*i)++;
	return (len);
}

static int	measure_without_q(t_shell *shell, char *input, int *i)
{
	int	len;

	len = 0;
	while (input[*i] && input[*i] != '\'' && input[*i] != '"')
	{
		if (input[*i] == '$' && input[*i + 1])
		{
			(*i)++;
			len += handle_env_var(shell, input, i);
		}
		else
		{
			len++;
			(*i)++;
		}
	}
	return (len);
}

static int	handle_env_var(t_shell *shell, char *input, int *i)
{
	char	*name;
	char	*value;
	int		len;

	name = parse_var_name(shell, input, i);
	if (!name)
    {
		return (0);
    }
	value = load_var_value(name, shell);
	len = 0;
	if (value)
	{
		len = ft_strlen(value);
		if (name[0] == '?' && name[1] == '\0')
        {
			free(value);
        }
	}
	free(name);
	return (len);
}


