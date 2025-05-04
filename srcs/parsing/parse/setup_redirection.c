#include "minishell.h"

static bool	handle_redirections(t_shell *shell, t_cmd *cmd);
static bool	handle_in_redir(t_shell *shell, t_cmd *cmd, t_dir *redir);
static bool	handle_out_redir(t_shell *shell, t_cmd *cmd, t_dir *redir);
static void	handle_heredoc_redir(t_cmd *cmd, t_dir *redir);

bool	setup_redirections_with_pipe(t_shell *shell, t_cmd *cmd, int i)
{
	if (!handle_redirections(shell, cmd))
	{
		if (i > 0 && shell->num_pipes_fd[i - 1][0] > 2)
		{
			close(shell->num_pipes_fd[i - 1][0]);
			shell->num_pipes_fd[i - 1][0] = -1;
		}
		if (i < shell->num_pipes && shell->num_pipes_fd[i][1] > 2)
		{
			close(shell->num_pipes_fd[i][1]);
			shell->num_pipes_fd[i][1] = -1;
		}
		return (false);
	}
	if (cmd->in_fd == STDIN_FILENO && i > 0)
	{
		cmd->in_fd = shell->num_pipes_fd[i - 1][0];
	}
	if (cmd->out_fd == STDOUT_FILENO && i < shell->num_pipes)
	{
		cmd->out_fd = shell->num_pipes_fd[i][1];
	}
	return (true);
}

static bool	handle_redirections(t_shell *shell, t_cmd *cmd)
{
	t_dir	*redir;

	redir = cmd->redir_list;
	while (redir)
	{
		if (!file_path_name_expansion(shell, redir))
			return (false);
		if (redir->type == DIR_IN)
		{
			if (!handle_in_redir(shell, cmd, redir))
				return (false);
		}
		else if (redir->type == DIR_OUT || redir->type == DIR_APPEND)
		{
			if (!handle_out_redir(shell, cmd, redir))
				return (false);
		}
		else if (redir->type == DIR_HEREDOC)
			handle_heredoc_redir(cmd, redir);
		redir = redir->next;
	}
	return (true);
}

static bool	handle_in_redir(t_shell *shell, t_cmd *cmd, t_dir *redir)
{
	t_dir	*prev;

	if (cmd->in_fd != STDIN_FILENO)
	{
		prev = redir->prev;
		if (prev && prev->type == DIR_HEREDOC)
		{
			if (prev->heredoc_fd[0] > 2)
				close(prev->heredoc_fd[0]);
			prev->heredoc_fd[0] = -1;
		}
		else
			close(cmd->in_fd);
	}
	cmd->in_fd = open(redir->filename, O_RDONLY);
	if (cmd->in_fd == -1)
	{
		print_open_error(redir->filename);
		shell->cur_exit_flag = 1;
		return (false);
	}
	return (true);
}

static bool	handle_out_redir(t_shell *shell, t_cmd *cmd, t_dir *redir)
{
	if (cmd->out_fd != STDOUT_FILENO)
		close(cmd->out_fd);
	if (redir->type == DIR_OUT)
		cmd->out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		cmd->out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->out_fd == -1)
	{
		print_open_error(redir->filename);
		shell->cur_exit_flag = 1;
		return (false);
	}
	return (true);
}

static void	handle_heredoc_redir(t_cmd *cmd, t_dir *redir)
{
	t_dir	*prev;

	if (cmd->in_fd != STDIN_FILENO)
	{
		prev = redir->prev;
		if (prev && prev->type == DIR_HEREDOC)
		{
			if (prev->heredoc_fd[0] > 2)
				close(prev->heredoc_fd[0]);
			prev->heredoc_fd[0] = -1;
		}
		else
			close(cmd->in_fd);
	}
	cmd->in_fd = redir->heredoc_fd[0];
}
