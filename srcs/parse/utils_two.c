#include "minishell.h"

t_bool is_interactive(t_shell *shell, char *input)
{
    if (is_quote_open(input) || ends_with_pipe(shell, input))
        return (C_TRUE);
}

t_bool	ends_with_pipe(t_shell *shell, char *input)
{
    int i;

	if (!input || !*input)
		return (0); // shut_program_err(shell); // TODO: handle null input // check later
	i = ft_strlen(input - 1);
	while (i >= 0 && input[i] == SPACE)
		i--;
	if (i >= 0 && input[i] == PIPE)
		return (C_TRUE);
	return (C_FALSE);
}

// ? Example: ["ls", "-l", "|", "grep", "minishell", ">", "|"]


// "ls -l | greep minishell > |          "

