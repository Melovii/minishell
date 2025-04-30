#include "minishell.h"

static void	parse_one_cmd(t_shell *shell, t_cmd *cmd);
static void	append_token_last(t_token **list, t_token *new_node);

int get_len_cmd_args(t_cmd *cmd)
{
    int len = 0;
    t_token *tmp = cmd->args;

    while (tmp)
    {
        len++;
        tmp = tmp->next;
    }
    return (len);
}

void	parser(t_shell *shell)
{
	t_cmd	*tail;

	shell->cmd = new_cmd_node(shell);
	tail = shell->cmd;
	while (shell->token)
	{
		parse_one_cmd(shell, tail);
		if (shell->token && shell->token->type == PIPE)
		{
			advance_token(shell);
			tail->next = new_cmd_node(shell);
			tail = tail->next;
		}
		else
			break ;
	}
}

static void	parse_one_cmd(t_shell *shell, t_cmd *cmd)
{
	t_token	*arg;

	while (shell->token && shell->token->type != PIPE)
	{
		if (is_redirection_type(shell->token->type))
        {
			parse_redirection(shell, cmd);
        }
		else if (shell->token->type == WORD)
		{
			arg = shell->token;
			shell->token = shell->token->next;
			append_token_last(&cmd->args, arg);
		}
		else
			break ;
	}
}

static void	append_token_last(t_token **list, t_token *new_node)
{
	t_token	*tmp;

	if (!new_node)
		return ;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}
