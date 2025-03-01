#include "minishell.h"

char	**tokenise_input(char *input)
{
	char	**final;

	// TODO:
	// Control ' and "  ---> by using sub-functions	
	// Split arguments and return tokenised input.
	// final process
	final = ft_split(input);
	if (!final)
		return (NULL);
	return (final);
}

// ? Example: ["ls", "-l", "|", "grep", "minishell", ">", "output.txt"]

void	process_input(char *input)
{
	// TODO:
	// Take input, call tokenise_input
	// Execute command
}
