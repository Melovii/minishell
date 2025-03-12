#include "minishell.h"

static t_bool is_heredoc(char *input, int *i)
{
	int j;

	j = *i;
	if (input[j + 1] == INPUT_RDRCT)
	{
		if (is_operator(input[j + 2]))
			return (C_FALSE);
		*i = j + 1;
		return (C_TRUE);
	}
	return (C_FALSE);
}

// * purpose: helper function that using recursive to find the limiter
static char *concat_limiter(t_shell *shell, char *input, int *i, char *limiter)
{
	if (input[*i] == '\0' || input[*i] == SPACE) // end of the limiter
		return (limiter);
	else if (is_operator(input[*i]))  // end of the limiter by coming operators
		return (limiter);
	else if (is_quote(input[*i]))
		return (concat_quote(shell, input, i, limiter));
	else
		return (concat_default(shell, input, i, limiter));
}

// !	if find_limiter return (NULL) that means there is a problem
// !	handle error management
static char *find_limiter(t_shell *shell, char *input, int i)
{
	i++;
	while (input[i] && input[i] == SPACE)
		i++;
	if (input[i] == '\0')
		return (NULL);
	return (concat_limiter(shell, input, &i, ft_strdup("")));
}

void heredoc_interactive(t_shell *shell, char *input)
{
	int	i;

	i = shell->heredoc_index;
	while (input[i])
	{
		if (input[i] == INPUT_RDRCT)
		{
			if (is_heredoc(input, &i))
			{
				cr_add_heredoc(shell, &(shell->heredoc_list), 
					find_limiter(shell, input, i));
			}
		}
		i++;
	}
	shell->heredoc_index = i;
}
