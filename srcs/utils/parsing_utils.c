#include "minishell.h"

// * Function to create and return a new token with the given value
static t_token	*new_token(char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	// ! potential error check
	token->next = NULL;
	token->type = NIL;
	return (token);
}

// * Function to add a new token to the token list
void	add_token(t_token **tokens, char *value)
{
	t_token	*new;
	t_token	*temp;

	new = new_token(value);
	if (!new)
		return ;
	if (!*tokens)
		*tokens = new;
	else
	{
		temp = *tokens;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

bool	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}
