#include "minishell.h"

/**
**	Purpose: Checks if the quotes in the input are balanced.
*	@input: The string to be checked for balanced quotes.
*/
bool	is_quote_open(char input[])
{
	int		i;
	char	current_quote;

	current_quote = '\0';  // Initialize to no quote (it is a flag)
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (current_quote == '\0')
				current_quote = input[i];
			else if (current_quote == input[i])
				current_quote = '\0';
		}
		i++;
	}
	return (current_quote != '\0');
}

