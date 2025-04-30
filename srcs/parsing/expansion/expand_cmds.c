#include "minishell.h"

static void	expand_token_values(t_shell *shell, t_token *token_lst);

void	expand_and_unquote_cmd_list(t_shell *shell)
{
	t_cmd	*cmd;

	if (!shell)
		return ;
	cmd = shell->cmd;
	while (cmd)
	{
		expand_token_values(shell, cmd->args);
		cmd = cmd->next;
	}
}

static void	expand_token_values(t_shell *shell, t_token *token_lst)
{
	while (token_lst)
	{
		token_lst->value = expand_vars(shell, token_lst->value);
		token_lst->value = remove_quotes_update_str(shell, token_lst->value);
		token_lst = token_lst->next;
	}
}
