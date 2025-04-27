#include "stdbool.h"
#include "minishell.h"
#include "stdio.h" // ! For testing purposes

bool    is_operator(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (true);
    return (false);
}

static bool	is_invalid_operator(char *value)
{
	return (are_strs_equal(value, "||")
		|| are_strs_equal(value, "&&")
		|| are_strs_equal(value, "&"));
}

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

bool	is_operator_type(t_token_type type)
{
	return (type == PIPE || type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == HEREDOC || type == APPEND);
}

bool	is_redirection_type(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == HEREDOC || type == APPEND);
}


void	print_tokens(t_token *tokens) // ! For testing purposes
{
    if (!tokens)
    {
        printf("No tokens to print.\n");
        return ;
    }
	while (tokens)
	{
		printf("Token Value: \"%s\", Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}
