#include "minishell.h"

// * Closes all unused pipe file descriptors except for the current one being used
void	close_unused_pipes(t_shell *shell, int current)
{
	int	i;

	i = 0;
    if (!shell->num_pipes_fd)
	{
        return ;
	}
	while (i < shell->num_pipes)
	{
		if (i != current && shell->num_pipes_fd[i][WRITE_END] != -1)
        {
			close(shell->num_pipes_fd[i][WRITE_END]);
            shell->num_pipes_fd[i][WRITE_END] = -1;
        }
		if (i != current - 1 && shell->num_pipes_fd[i][READ_END] != -1)
        {
			close(shell->num_pipes_fd[i][READ_END]);
            shell->num_pipes_fd[i][READ_END] = -1;
        }
		i++;
	}
}

// * Closes all pipe file descriptors that are open
void	close_all_pipes(t_shell *shell)
{
	int	i;

	if (!shell->num_pipes_fd)
		return;
	i = 0;
	while (i < shell->num_pipes)
	{
		if (shell->num_pipes_fd[i][READ_END] >= 0)
		{
			close(shell->num_pipes_fd[i][READ_END]);
			shell->num_pipes_fd[i][READ_END] = -1;
		}
		if (shell->num_pipes_fd[i][WRITE_END] >= 0)
		{
			close(shell->num_pipes_fd[i][WRITE_END]);
			shell->num_pipes_fd[i][WRITE_END] = -1;
		}
		i++;
	}
}

// * Closes input and output redirection file descriptors for commands in the list
void close_redirections(t_cmd *cmd_list)
{
    t_cmd *cmd = cmd_list;
    while (cmd)
    {
        if (has_input_redirection_via_list(cmd) && cmd->in_fd > STDIN_FILENO)
        {
            close(cmd->in_fd);
            cmd->in_fd = -1;
        }
        if (has_output_redirection_via_list(cmd) && cmd->out_fd > STDOUT_FILENO)
        {
            close(cmd->out_fd);
            cmd->out_fd = -1;
        }
        cmd = cmd->next;
    }
}
