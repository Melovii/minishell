#include "minishell.h"

static void	tokenise_input(t_shell *shell, char *input)
{
	// TODO:
	// Control default input that without operators and quotes
	// Control ' and "  ---> by using sub-functions
	// Control operators ('|', '>>', '<<', '>', '<')
	// Split arguments and return tokenised linked list.
	// final process

	int	i;

	i = -1;

	while (input[++i])
	{
		if (input[i] == SPACE)
			continue ;
		else if (is_operator(input[i]))
			token_operator(shell, input, &i);
		else if (is_quote(input[i]))
			token_quote(shell, input, &i);
		else
			token_default(shell, input, &i, NULL);
	}
}

// ? Example: ["ls", "-l", "|", "grep", "minishell", ">", "output.txt"]

void	process_input(t_shell *shell, char *input)
{
	// TODO:
	// Take input, call tokenise_input
	// Execute command

	tokenise_input(shell, input);
}
