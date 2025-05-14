#include "minishell.h"

static bool	check_invalid_operator(t_token *tokens);
static bool	check_token_pair_syntax(t_token *prev, t_token *tokens);
static bool	check_last_token_syntax(t_shell *shell, t_token *prev);
static bool	check_first_token_syntax(t_token *tokens);

// * Checks the overall syntax of a list of tokens
bool	check_syntax(t_shell *shell, t_token *tokens)
{
	t_token	*prev;

	if (!tokens)
		return (false);
	if (!check_first_token_syntax(tokens))
	{
		shell->cur_exit_flag = 1;
		return (false);
	}
	prev = NULL;
	while (tokens)
	{
		if (!check_token_pair_syntax(prev, tokens)
			|| !check_invalid_operator(tokens))
		{
			shell->cur_exit_flag = 1;
			return (false);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (check_last_token_syntax(shell, prev));
}

// * Checks if the token is an invalid operator and prints an error message
static bool	check_invalid_operator(t_token *tokens)
{
	if (tokens->type == INV_OPERATOR)
	{
		ft_putstr_fd("minishell: syntax error near invalid operator `",
			STDERR_FILENO);
		ft_putstr_fd(tokens->value, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		return (false);
	}
	return (true);
}

// * Checks the syntax between two tokens, ensuring no invalid token pairs exist
static bool	check_token_pair_syntax(t_token *prev, t_token *tokens)
{
	if (!prev)
		return (true);
	if (is_operator_type(prev->type) && is_operator_type(tokens->type))
	{
		if (!(prev->type == PIPE && is_redirection_type(tokens->type)))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `",
				STDERR_FILENO);
			ft_putstr_fd(tokens->value, STDERR_FILENO);
			ft_putendl_fd("'", STDERR_FILENO);
			return (false);
		}
	}
	if (is_redirection_type(prev->type) && tokens->type != WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(tokens->value, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		return (false);
	}
	return (true);
}

// * Checks the syntax of the last token to ensure it's valid
static bool	check_last_token_syntax(t_shell *shell, t_token *tokens)
{
	while (tokens->next)
		tokens = tokens->next;
	if (is_operator_type(tokens->type))
	{
		ft_putendl_fd(SYN_ERR_MSG_1, STDERR_FILENO);
		shell->cur_exit_flag = 1;
		return (false);
	}
	return (true);
}

// * Checks the syntax of the first token to ensure it's valid
static bool	check_first_token_syntax(t_token *tokens)
{
	if (tokens->type == PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'",
			STDERR_FILENO);
		return (false);
	}
	if (is_redirection_type(tokens->type))
	{
		if (!tokens->next)
		{
			ft_putendl_fd(SYN_ERR_MSG_1, STDERR_FILENO);
			return (false);
		}
		if (tokens->next->type != WORD)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `",
				STDERR_FILENO);
			ft_putstr_fd(tokens->next->value, STDERR_FILENO);
			ft_putendl_fd("'", STDERR_FILENO);
			return (false);
		}
	}
	return (true);
}
