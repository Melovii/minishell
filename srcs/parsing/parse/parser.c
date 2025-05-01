#include "minishell.h"

static void	append_arg_node(t_token **args, t_token *new_node);
static void	parse_command(t_shell *shell, t_cmd *cmd);

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
		parse_command(shell, tail);
		if (shell->token && shell->token->type == PIPE)
		{
			shell->token = shell->token->next;
			tail->next = new_cmd_node(shell);
			tail = tail->next;
		}
		else
			break ;
	}
}

static void	parse_command(t_shell *shell, t_cmd *cmd)
{
	while (shell->token && shell->token->type != PIPE)
	{
		if (is_redirection_type(shell->token->type))
			parse_redirection(shell, cmd);
		else if (shell->token->type == WORD)
		{
			t_token *cur = shell->token;
			shell->token = shell->token->next;
			cur->next = NULL;
			append_arg_node(&cmd->args, cur);
		}
		else
			shell->token = shell->token->next;
	}
}


static void	append_arg_node(t_token **args, t_token *new_node)
{
	t_token	*cur;

	new_node->next = NULL;
	if (!*args)
	{
		*args = new_node;
		return ;
	}
	cur = *args;
	while (cur->next)
		cur = cur->next;
	cur->next = new_node;
}

