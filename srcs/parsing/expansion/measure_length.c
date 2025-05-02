#include "minishell.h"
#include "../libft/libft.h"

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

static int measure_sq(char *s, int *i)
{
	int len;

	len = 0;
	(*i)++;
	while (s[*i] && s[*i] != '\'')
	{
		len++;
		(*i)++;
	}
	if (s[*i] == '\'')
		(*i)++;
	return (len + 2);
}

static int measure_without_q(t_shell *shell, char *s, int *i)
{
	int len;

	len = 0;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"')
	{
		if (s[*i] == '$')
		{
			len += handle_env_var_len(shell, s, i, false);
			break ;
		}
		len++;
		(*i)++;
	}
	return (len);
}

static int measure_dq(t_shell *shell, char *s, int *i)
{
	int len;

	len = 0;
	(*i)++;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
		{
			len += handle_env_var_len(shell, s, i, true);
			break ;
		}
		len++;
		(*i)++;
	}
	if (s[*i] == '"')
		(*i)++;
	return (len + 2);
}
