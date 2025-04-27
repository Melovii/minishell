#include "minishell.h"
#include "../libft/libft.h"

static char    *get_filename(t_shell *shell);
static t_redir_type    get_redir_type(t_shell *shell, t_token *token);

void    parse_redirection(t_shell *shell, t_cmd *cmd)
{
    t_token     *token;
    char        *file;
    t_redir_type dir_type;
    t_dir       *redir;

    token = shell->token;
    advance_token(shell);
    file = get_filename(shell);
    dir_type = get_redir_type(shell, token);
    redir = create_redir_node(shell, dir_type, file);
    if (!redir)
    {
        free(file);
        shut_program(shell, true , EX_KO);
    }
    add_redir_node(&cmd->redir_list, redir);
}

static t_redir_type    get_redir_type(t_shell *shell, t_token *token)
{
    if (token->type == REDIRECT_IN)
        return (DIR_IN);
    if (token->type == REDIRECT_OUT)
        return (DIR_OUT);
    if (token->type == APPEND)
        return (DIR_APPEND);
    if (token->type == HEREDOC)
        return (DIR_HEREDOC);
    ft_putendl_fd("minishell: Invalid redirection type", STDERR_FILENO);
    shut_program(shell, false, EX_KO);
    return (DIR_IN); // Unreachable, for norm compliance
}


static char    *get_filename(t_shell *shell)
{
    char    *file;

    if (!shell->token || shell->token->type != WORD)
    {
        ft_putendl_fd("minishell: Expected filename after redir", STDERR_FILENO);
        shut_program(shell, false, EX_KO);
    }
    file = ft_strdup(shell->token->value);
    if (!file)
        shut_program(shell, true, EX_KO);
    advance_token(shell);
    return (file);
}

bool	has_output_redirection_via_list(t_cmd *cmd)
{
	t_dir	*redir;

	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->type == DIR_OUT || redir->type == DIR_APPEND)
			return (true);
		redir = redir->next;
	}
	return (false);
}

bool	has_input_redirection_via_list(t_cmd *cmd)
{
	t_dir	*redir;

	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->type == DIR_IN || redir->type == DIR_HEREDOC)
			return (true);
		redir = redir->next;
	}
	return (false);
}

