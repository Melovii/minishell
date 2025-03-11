#include "minishell.h"

static void	fill_one_heredoc(t_shell *shell, t_heredoc *node);
static void fill_the_buffer(t_shell *shell, t_heredoc *node, char *added);

void display_heredoc_list(t_heredoc *head)
{
    t_heredoc *current = head;

    while (current != NULL)
    {
        printf("Heredoc #%d\n", current->no);
        printf("  Limiter   : %s\n", current->limiter ? current->limiter : "(null)");
        printf("  File Name : %s\n", current->file_name ? current->file_name : "(null)");
        printf("  Is Filled : %s\n", current->is_filled ? "true" : "false");
        printf("\n");
        current = current->next;
    }
}

void	fill_heredocs(t_shell *shell)
{
	t_heredoc *heredoc_head;

	heredoc_head = shell->heredoc_list;
	display_heredoc_list(heredoc_head);
	while  (heredoc_head)
	{
		if (heredoc_head->is_filled == C_FALSE)
			fill_one_heredoc(shell, heredoc_head);
		heredoc_head = heredoc_head->next;
	}
}

static void	fill_one_heredoc(t_shell *shell, t_heredoc *node)
{
	char *added;

	while (1)
	{
		shell->history = ultimate_join(shell, shell->history, ft_strdup("\n"));
		added = readline("heredoc> ");
		if (!added)
			shut_program_err(shell);
		shell->history = ultimate_join(shell, shell->history, ft_strdup(added));
		if (are_strs_equal(added, node->limiter))
		{
			node->is_filled = C_TRUE;
			break ;
		}
		fill_the_buffer(shell, node, added);
		free(added);
	}
}

static void fill_the_buffer(t_shell *shell, t_heredoc *node, char *added)
{
	int	fd;

	fd = open(node->file_name, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (fd < 0)
		shut_program_err(shell); // ! check later
	ft_putendl_fd(added, fd);
}
