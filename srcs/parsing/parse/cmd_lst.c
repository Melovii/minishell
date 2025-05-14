#include "minishell.h"

// * Creates a new command node and initializes its fields
t_cmd	*new_cmd_node(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		shut_program(shell, true, EX_KO);
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
	cmd->next = NULL;
	cmd->args = NULL;
    cmd->redir_list = NULL;
	return (cmd);
}

// * Frees all nodes in the redirection list and closes open heredoc fds
static void    free_redir_list(t_dir *redir)
{
    t_dir *tmp;

    while (redir)
    {
        tmp = redir->next;
        if (redir->filename)
            free(redir->filename);
		if (redir->heredoc_fd[READ_END] > 2)
			close(redir->heredoc_fd[READ_END]);
		if (redir->heredoc_fd[WRITE_END] > 2)
			close(redir->heredoc_fd[WRITE_END]);
        free(redir);
        redir = tmp;
    }
}

// * Frees the entire command list including redirections and arguments
void	free_cmd_list(t_cmd *head)
{
	t_cmd	*curr;
	t_cmd	*next;

	curr = head;
	while (curr)
	{
		next = curr->next;
		if (curr->args)
			free_tokens(curr->args);
		if (curr->redir_list)
			free_redir_list(curr->redir_list);
		free(curr);
		curr = next;
	}
}

// * Creates a new redirection node with the specified type and filename
	t_dir *create_redir_node(t_shell *shell, t_redir_type type, char *filename)
{
    t_dir *new;
	(void)shell;

    new = ft_calloc(1, sizeof(t_dir));
    if (!new)
        return (NULL);
    new->type = type;
    new->filename = filename;
    new->heredoc_fd[READ_END] = -1;
    new->heredoc_fd[WRITE_END] = -1;
    new->next = NULL;
	new->prev = NULL;
    return (new);
}

// * Adds a redirection node to the end of the redirection list
void add_redir_node(t_dir **redir_list, t_dir *new_node)
{
    t_dir *current;

    if (!redir_list || !new_node)
        return ;
    if (!*redir_list)
    {
        *redir_list = new_node;
        return ;
    }
    current = *redir_list;
    while (current->next)
        current = current->next;
    current->next = new_node;
	new_node->prev = current;
}

// * Prints the redirection list for debugging purposes
void    print_redir_list(t_dir *redir)
{
    while (redir)
    {
        printf("  redirection: ");
        if (redir->type == DIR_IN)
            printf("< ");
        else if (redir->type == DIR_OUT)
            printf("> ");
        else if (redir->type == DIR_APPEND)
            printf(">> ");
        else if (redir->type == DIR_HEREDOC)
            printf("<< ");

        if (redir->filename == NULL)
            printf("(NULL)\n");
        else
            printf("%s\n", redir->filename);
        
        redir = redir->next;
    }
}
