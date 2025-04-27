#include "minishell.h"

char	*expand_vars( t_shell *shell, char *input)
{
	int		len;
	char	*res;

	len = measure_len(shell, input);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
    {
		shut_program(shell, true, EX_KO);
    }
	// * We need to fill the string with the right values
	return (res);
}
