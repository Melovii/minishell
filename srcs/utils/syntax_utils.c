#include "minishell.h"


static bool	check_invalid_operator(t_token *tokens);
static bool	check_token_pair_syntax(t_token *prev, t_token *tokens);
static bool	check_last_token_syntax(t_token *prev);
static bool	check_first_token_syntax(t_token *tokens);

bool	check_syntax(t_token *tokens)
{
	t_token	*prev;

	if (!tokens)
		return (false);
	if (!check_first_token_syntax(tokens))
		return (false);
	prev = NULL;
	while (tokens)
	{
		if (!check_token_pair_syntax(prev, tokens))
			return (false);
		if (!check_invalid_operator(tokens))
			return (false);
		prev = tokens;
		tokens = tokens->next;
	}
	return (check_last_token_syntax(prev));
}

static bool	check_invalid_operator(t_token *tokens)
{
	if (tokens->type == INV_OPERATOR)
	{
		ft_putstr_fd("minishell: syntax error near invalid operator `", 2);
		ft_putstr_fd(tokens->value, 2);
		ft_putendl_fd("'", 2);
		return (false);
	}
	return (true);
}

static bool	check_token_pair_syntax(t_token *prev, t_token *tokens)
{
	if (!prev)
		return (true);
	if (is_operator_type(prev->type) && is_operator_type(tokens->type))
	{
		if (!(prev->type == PIPE && is_redirection_type(tokens->type)))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(tokens->value, 2);
			ft_putendl_fd("'", 2);
			return (false);
		}
	}
	if (is_redirection_type(prev->type) && tokens->type != WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tokens->value, 2);
		ft_putendl_fd("'", 2);
		return (false);
	}
	return (true);
}

static bool	check_last_token_syntax(t_token *tokens)
{
	if (!tokens)
		return (false);
	while (tokens->next)
		tokens = tokens->next;
	if (is_operator_type(tokens->type))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
		return (false);
	}
	return (true);
}

static bool	check_first_token_syntax(t_token *tokens)
{
	if (!tokens)
		return (false);
	if (tokens->type == PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (false);
	}
	if (is_redirection_type(tokens->type))
	{
		if (!tokens->next)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
			return (false);
		}
		if (tokens->next->type != WORD)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(tokens->next->value, 2);
			ft_putendl_fd("'", 2);
			return (false);
		}
	}
	return (true);
}
