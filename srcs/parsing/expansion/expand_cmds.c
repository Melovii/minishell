#include "minishell.h"

static void	expand_and_unquote(t_shell *shell, t_token *token_lst);
static void	remove_null_value_tokens(t_token **head);

// * Expands variables and removes quotes from the command arguments in the command list
void	expand_and_unquote_cmd_list(t_shell *shell)
{
	t_cmd	*cmd;

	if (!shell)
		return ;
	cmd = shell->cmd;
	while (cmd)
	{
		expand_and_unquote(shell, cmd->args);
		remove_null_value_tokens(&(cmd->args));
		cmd = cmd->next;
	}
}

// * Expands variables and removes quotes for each token in the token list
static void	expand_and_unquote(t_shell *shell, t_token *token_lst)
{
	while (token_lst)
	{
		token_lst->value = expand_vars(shell, token_lst->value);
		token_lst->value = remove_quotes_update_str(shell, token_lst->value);
		token_lst = token_lst->next;
	}
}

// * Removes tokens with NULL values from the token list in the command structure
static void	remove_null_value_tokens(t_token **head)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*to_delete;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		if (!curr->value)
		{
			to_delete = curr;
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			curr = curr->next;
			free_token_node(to_delete);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

