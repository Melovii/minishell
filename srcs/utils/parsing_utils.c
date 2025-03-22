#include "minishell.h"

char **refill_cmd_args(char **old, int len, char *value)
{
	char	**new;
	int	i;

	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[len] = ft_strdup(value);
	if (!(new[len]))
		return (NULL);  // ! check for error handling
	new[len + 1] = NULL;
	free(old);
	return (new);
}
// * Purpose: To initialize cmd structure with initial values
void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->in_fd = -1;
	cmd->out_fd = -1;
	cmd->next = NULL;
}

// * Function to create and return a new token with the given value
static t_token	*new_token(char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->next = NULL;
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
