#include "minishell.h"

static void	clean_one_heredoc(t_heredoc *node)
{
	if (!node)
		return ;
	if (node->file_name)
	{
		unlink(node->file_name);
		free(node->file_name);
	}
	free(node->limiter);
	free(node);
}

void	clear_heredoc(t_shell *shell)
{
	t_heredoc	*heredoc_head;
	t_heredoc	*temp;

	if (!shell || !(shell->heredoc_list))
		return ;
	heredoc_head = shell->heredoc_list;
	while (heredoc_head)
	{
		temp = heredoc_head->next;
		clean_one_heredoc(heredoc_head);
		heredoc_head = temp;
	}
	shell->heredoc_list = NULL;
}
