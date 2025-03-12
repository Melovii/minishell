#include "minishell.h"

//* purpose: creating a new token node (without any connection)
t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = ft_strdup(value);
	if (new->value == NULL)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

//! check later
// * purpose: add a new node last of token linked list
void	add_token_back(t_shell *shell, t_token **token_head, t_token *added)
{
	t_token	*temp_head;

	if (token_head == NULL)
		shut_program_err(shell); //! check later
	if (*token_head == NULL)
	{
		*token_head = added;
		return ;
	}
	temp_head = *token_head;
	while (temp_head->next)
		temp_head = temp_head->next;
	temp_head->next = added;
}

//! check later
// * name: create and add token
// * purpose: combine add_token_back() and new_token() functions
// * parameters:	(shell)-> main struct, (h/head)-> head of token list,
// * 				(v/value)-> value of the node,
// *				(type)-> type of the token
void	cr_add_token(t_shell *shell, t_token **h, char *v, t_token_type type)
{
	t_token	*new;

	new = new_token(v, type);
	if (!new)
		shut_program_err(shell); //! check later
	add_token_back(shell, h, new);
}
