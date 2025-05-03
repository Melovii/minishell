#include "minishell.h"
#include "../libft/libft.h"

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

static void    free_redir_list(t_dir *redir)
{
    t_dir *tmp;

    while (redir)
    {
        tmp = redir->next;
        if (redir->filename)
            free(redir->filename);
        free(redir);
        redir = tmp;
    }
}

void    free_cmd_list(t_cmd *head)
{
    t_cmd *curr;
    t_cmd *next;

    curr = head;
    while (curr)
    {
        next = curr->next;
        if (curr->args)
            free_tokens(curr->args);
        if (curr->redir_list)
            free_redir_list(curr->redir_list);
        if (curr->in_fd > 2)
        {
            close(curr->in_fd);
            curr->in_fd = -1;
        }
        if (curr->out_fd > 2)
        {
            close(curr->out_fd);
            curr->out_fd = -1;
        }
        free(curr);
        curr = next;
    }
}

t_dir *create_redir_node(t_shell *shell, t_redir_type type, char *filename)
{
    t_dir *new;

    new = ft_calloc(1, sizeof(t_dir));
    if (!new)
        return (NULL);
    new->type = type;
    new->filename = filename;
    new->heredoc_fd[0] = -1;
    new->heredoc_fd[1] = -1;
    new->next = NULL;
    return (new);
}

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
}

// ! Will be removed later, for debugging purposes ===========================

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

void	print_cmd_list(t_cmd *head)
{
	t_cmd	*curr = head;
	t_token	*arg;

	while (curr)
	{
		printf("Command:\n  args:");
		arg = curr->args;
		if (!arg)
			printf(" (none)");
		while (arg)
		{
			if (!arg->value)
				printf(" (NULL)");
			else if (arg->value[0] == '\0')
				printf(" (empty string)");
			else
				printf(" \"%s\"", arg->value);
			arg = arg->next;
		}
		printf("\n");

		if (curr->redir_list)
			print_redir_list(curr->redir_list);
		else
			printf("  redirection: (none)\n");

		curr = curr->next;
	}
}



