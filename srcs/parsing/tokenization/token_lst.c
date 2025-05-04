#include "../libft/libft.h"
#include "minishell.h"

static t_token	*new_token(char *value);

void    free_tokens(t_token *tokens)
{
    t_token	*temp;

    while (tokens)
    {
        temp = tokens;
        tokens = tokens->next;
        free(temp->value);
        free(temp);
    }
}

void	add_token(t_shell *shell, t_token **tokens, char *value)
{
	t_token	*new;
	t_token	*temp;

    if (!value)
	{
        shut_program(shell, true, EX_KO);
	}
	new = new_token(value);
	if (!new)
    {
        free(value);
		shut_program(shell, true, EX_KO);
    }
	if (!(*tokens))
		*tokens = new;
	else
	{
		temp = *tokens;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	free_token_node(t_token *node)
{
	if (!node)
		return ;
	free(node->value);
	free(node);
}

void	advance_token(t_shell *shell)
{
	if (shell->token)
		shell->token = shell->token->next;
}

static t_token	*new_token(char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
    {
        free(token);
        return (NULL);
    }
	token->next = NULL;
	token->type = NIL;
	return (token);
}
