#include "minishell.h"

static t_token  *collect_args_list(t_shell *shell);

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
    t_cmd *tail;

    shell->cmd = new_cmd_node(shell);
    tail = shell->cmd;
    while (shell->token)
    {
        while (shell->token && shell->token->type != PIPE)
        {
            if (is_redirection_type(shell->token->type))
                parse_redirection(shell, tail);
            else if (shell->token->type == WORD)
                tail->args = collect_args_list(shell);
            else
                break ;
        }
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

static t_token  *collect_args_list(t_shell *shell)
{
    t_token *start;
    t_token *end;

    start = NULL;
    end = NULL;
    while (shell->token && shell->token->type == WORD)
    {
        if (!start)
            start = shell->token;
        end = shell->token;
        shell->token = shell->token->next;
    }
    if (end)
        end->next = NULL;
    return (start);
}
