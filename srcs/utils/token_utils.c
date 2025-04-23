#include "minishell.h"

static void	check_token_type(t_token *token);

void    update_token_type(t_token *token)
{
    t_token *token_lst;

    token_lst = token;
    while (token_lst)
    {
        check_token_type(token_lst);
        token_lst = token_lst->next;
    }
}

static void	check_token_type(t_token *token)
{
	if (are_strs_equal(token->value, "<<"))
		token->type = HEREDOC;
	else if (are_strs_equal(token->value, ">>"))
		token->type = APPEND;
	else if (are_strs_equal(token->value, "|"))
		token->type = PIPE;
	else if (are_strs_equal(token->value, "<"))
		token->type = REDIRECT_IN;
	else if (are_strs_equal(token->value, ">"))
		token->type = REDIRECT_OUT;
	else
		token->type = WORD;
}

// TODO: Handle Invalid Operators such as '>>>' '<<<' '&&' '||'