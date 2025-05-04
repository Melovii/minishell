#include "minishell.h"

// * Checks if the character is a shell operator (|, <, or >)
bool    is_operator(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (true);
    return (false);
}

// * Checks if the given string represents an invalid operator (e.g., "||", "&&", "&")
static bool	is_invalid_operator(char *value)
{
	return (are_strs_equal(value, "||")
		|| are_strs_equal(value, "&&")
		|| are_strs_equal(value, "&"));
}

// * Updates the token type based on its value (e.g., "|", "<", ">>", etc.)
void	update_token_type(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == NIL)
		{
			if (are_strs_equal(tokens->value, "|"))
				tokens->type = PIPE;
			else if (are_strs_equal(tokens->value, "<"))
				tokens->type = REDIRECT_IN;
			else if (are_strs_equal(tokens->value, ">"))
				tokens->type = REDIRECT_OUT;
			else if (are_strs_equal(tokens->value, "<<"))
				tokens->type = HEREDOC;
			else if (are_strs_equal(tokens->value, ">>"))
				tokens->type = APPEND;
			else if (is_invalid_operator(tokens->value))
				tokens->type = INV_OPERATOR;
			else
				tokens->type = WORD;
		}
		tokens = tokens->next;
	}
}

// * Checks if the token type is an operator (pipe or redirection)
bool	is_operator_type(t_token_type type)
{
	return (type == PIPE || type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == HEREDOC || type == APPEND);
}

// * Checks if the token type is a redirection (input, output, heredoc, or append)
bool	is_redirection_type(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == HEREDOC || type == APPEND);
}
