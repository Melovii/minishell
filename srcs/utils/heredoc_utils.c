#include "minishell.h"

// TODO: move this back to heredoc.c if possible
// redirect command's stdin to the heredoc fd
void	redirect_heredoc(t_cmd *cmd)
{
	// dup2(cmd->heredoc_fd, STDIN_FILENO);
	// close(cmd->heredoc_fd);
	// ? cmd->heredoc_fd = -1;
}