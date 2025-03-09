#include "minishell.h"

t_bool is_interactive(t_shell *shell)
{
	shell->num_heredoc = count_heredoc(shell);
    if (is_quote_open(shell) || ends_with_pipe(shell)
		|| does_any_heredoc_remain(shell))
        return (C_TRUE);
	return (C_FALSE);
}

t_bool	ends_with_pipe(t_shell *shell)
{
	int i;

	if (!(shell->input))
		shut_program_err(shell);	// TODO: change error handling implementation
	i = ft_strlen(shell->input) - 1;
	while (i >= 0 && shell->input[i] == SPACE)
		i--;
	if (i >= 0 && shell->input[i] == PIPE)
		return (C_TRUE);
	return (C_FALSE);
}

t_bool	does_any_heredoc_remain(t_shell *shell)
{
	if (heredoc_list_len(shell->heredoc_list) == count_heredoc(shell))
		return (C_FALSE);
	return (C_TRUE);
}


int	count_heredoc(t_shell *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(shell->input[i + 1])
	{
		// TODO: add a check for cases such as "<<<"
		if (shell->input[i] == '<' && shell->input[i + 1] == '<')
		{
			if (!is_operator(shell->input[i + 2]))
				count++;
			i += 2;
		}
		i++;
	}
	// printf("%d\n", count);
	return (count);
}

// ? Example: ["ls", "-l", "|", "grep", "minishell", ">", "|"]


// "ls -l | greep minishell > |          "
