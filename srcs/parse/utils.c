#include "minishell.h"

t_bool	is_operator(char c)
{
	if (c == INPUT_RDRCT || c == OUTPUT_RDRCT | c == PIPE)
		return (C_TRUE);
	return (C_FALSE);
}

t_bool	is_quote(char c)
{
	if (c == DOUBLE_QUOTE || c == SINGLE_QUOTE)
		return (C_TRUE);
	return (C_FALSE);
}

char *ultimate_join(t_shell *shell, char *s1, char *s2)
{
	char *new;

	new = ft_strjoin(s1, (s2));
	if (!new)
	{
		free(s1);
		free(s2);
		shut_program_err(shell);
	}
	free(s1);
	free(s2);
	return (new);
}
