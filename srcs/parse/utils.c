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
