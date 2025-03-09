#include "minishell.h"

void	handle_interactive(t_shell *shell, char *input)
{
	if (is_quote_open(input))
		print("quote is open\n");
	else if (ends_with_pipe(shell, input))
		printf("ends with pipe\n");
}
