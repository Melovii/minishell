#include "minishell.h"
#include "../libft/libft.h"

static int	handle_env_var(t_shell *shell, char *s, int *i);
static int	measure_without_q(t_shell *shell, char *s, int *i);
static int	measure_sq(char *s, int *i);
static int	measure_dq(t_shell *shell, char *s, int *i);

int measure_len(t_shell *shell, char *input)
{
    int len;
    int i;

    len = 0;
    i = 0;
    while (input[i]) 
    {
        if (input[i] == '\'') 
        {
            len += measure_sq(input, &i);
        }
        else if (input[i] == '"')
        {
            len += measure_dq(shell, input, &i);
        }
        else
        {
            len += measure_without_q(shell, input, &i);
        }
    }
    return (len);
}

static int	measure_sq(char *input, int *i)
{
	int	len;

	len = 0;
	(*i)++;
	while (input[*i] && input[*i] != '\'')
	{
		len++;
		(*i)++;
	}
	if (input[*i] == '\'')
		(*i)++;
	return (len);
}


static int	measure_dq(t_shell *shell, char *input, int *i)
{
	int	len;

	len = 0;
	(*i)++;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$' && input[*i + 1] && input[*i + 1] != '"')
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
	if (input[*i] == '"')
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
	value = load_var_value(shell, name);
	len = 0;
	if (value)
	{
		len = ft_strlen(value);
	}
	free(name); 
	return (len);
}


