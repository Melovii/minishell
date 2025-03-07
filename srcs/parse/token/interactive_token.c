#include "minishell.h"


// * purpose: getting input until the interactive mode ends
char	*interactive_loop(t_shell *shell, char *input)
{
	char	*ext_input; //extended_input
	char	*add;

	while (1)
	{
		input = ultimate_join(shell, input, ft_strdup("\n")); // !because of the free function "\n add by strdup"
		add = readline("> ");
		if (!add)
			return (NULL);
		input = ultimate_join(shell, input, add);
		if (!is_quote_open(input))
			return (input);
	}
}
