#include "minishell.h"

// ! all wrong :(
// * purpose: tokenizing default input
// * parameters:	(shell)-> main struct, (input)-> str from client
// *				(i/index)-> current input index
// TODO: Tokenize Deafult
void	token_default(t_shell *shell, char *input, int *i)
{
	
}

static int	determine_len(char *input, int *i)
{
	int	j;
	int	len;

	j = *i;
	len = 0;
	while (!(is_operator(input[j]) || input[j] == '\0' || input[j] == SPACE))
	{
		if (input[j] == DOUBLE_QUOTE || input[j] == SINGLE_QUOTE)
		{
			j++;
			continue ;
		}
		len++;
		j++;
	}
	return (len);
}
