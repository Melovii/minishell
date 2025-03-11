#include "minishell.h"

static	t_bool	does_complete(char *input, int *i, char quote_type);

t_bool	is_operator(char c)
{
	if (c == INPUT_RDRCT || c == OUTPUT_RDRCT || c == PIPE)
		return (C_TRUE);
	return (C_FALSE);
}

t_bool	is_quote(char c)
{
	if (c == DOUBLE_QUOTE || c == SINGLE_QUOTE)
		return (C_TRUE);
	return (C_FALSE);
}
// * purpose: check the whole string whether is completed or not by quotes
t_bool	is_quote_open(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->input[++i])
	{
		if (is_quote(shell->input[i]))
		{
			if (!does_complete(shell->input, &i, shell->input[i]))
				return (C_TRUE);
		}
	}
	return (C_FALSE);
}

// * purpose: check whether quote is completed or not
static	t_bool	does_complete(char *input, int *i, char quote_type)
{
	(*i) += 1; // pass the first quote
	while (input[*i])
	{
		if (input[*i] == quote_type)
		{
			return (C_TRUE);
		}
		(*i) += 1;
	}
	return (C_FALSE);
}

char *ultimate_join(t_shell *shell, char *s1, char *s2)
{
	char *new;

	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (!new)
		shut_program_err(shell);
	return (new);
}
