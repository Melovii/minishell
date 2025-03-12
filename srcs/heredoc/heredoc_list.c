#include "minishell.h"

//* purpose: creating a new here_doc node (without any connection)
t_heredoc	*new_heredoc(char *limiter)
{
	t_heredoc	*new;

	new = ft_calloc(1, sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->limiter = limiter;
	new->is_filled = C_FALSE;
	return (new);
}

//! check later
// * purpose: add a new node last of heredoc linked list
void	add_heredoc_back(t_shell *shell, t_heredoc **heredoc_head,
		t_heredoc *added)
{
	t_heredoc	*temp_head;

	if (heredoc_head == NULL)
		shut_program_err(shell); //! check later
	if (*heredoc_head == NULL)
	{
		*heredoc_head = added;
		return ;
	}
	temp_head = *heredoc_head;
	while (temp_head->next)
		temp_head = temp_head->next;
	temp_head->next = added;
}

int	heredoc_list_len(t_heredoc *head)
{
	int	len;

	len = 0;
	while (head)
	{
		head = head->next;
		len++;
	}
	return (len);
}

//! check later
// * name: create and add heredoc
// * purpose: combine add_heredoc_back() and new_heredoc() functions
// * parameters:	(shell)-> main struct, (h/head)-> head of heredoc list,
// *				(limiter)-> limiter of the heredoc
void	cr_add_heredoc(t_shell *shell, t_heredoc **h, char *limiter)
{
	t_heredoc	*new;

	new = new_heredoc(limiter);
	if (!new)
		shut_program_err(shell); //! check later
	new->file_name = ft_itoa(heredoc_list_len(*h));
	new->no = heredoc_list_len(*h) + 1;
	add_heredoc_back(shell, h, new);
}
