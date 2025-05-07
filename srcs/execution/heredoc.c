#include "minishell.h"

static char *update_heredoc_prompt(t_shell *shell, bool is_quoted, char *line);
static int	setup_heredoc(t_shell *shell, t_dir *redir);
static void	handle_heredoc_child(t_shell *shell, t_dir *redir);
static int	wait_for_heredoc_child(pid_t pid);

// * Processes all heredoc redirections in the shell command list
int	process_heredocs(t_shell *shell)
{
	t_cmd	*cmd;
	t_dir	*redir;
	int		result;

	cmd = shell->cmd;
	while (cmd)
	{
		redir = cmd->redir_list;
		while (redir)
		{
			if (redir->type == DIR_HEREDOC)
			{
				result = setup_heredoc(shell, redir);
				if (result != EX_OK)
					return (result); // error or interrupt
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (EX_OK);
}

// * Sets up the pipe and forks a child process for heredoc input handling
static int	setup_heredoc(t_shell *shell, t_dir *redir)
{
	pid_t	pid;

	if (pipe(redir->heredoc_fd) == -1)
	{
		shut_program(shell, true, EX_KO);
		return (HEREDOC_PIPE_ERROR); // * Cannot be reached
	}
	pid = fork();
	if (pid < 0)
	{
		shut_program(shell, true, HEREDOC_FORK_ERROR);
		return (HEREDOC_FORK_ERROR); // * Cannot be reached
	}
	else if (pid == 0)
	{
		handle_signals(EXEC_HRDC);
		handle_heredoc_child(shell, redir);
	}
	close(redir->heredoc_fd[WRITE_END]);
	redir->heredoc_fd[WRITE_END] = -1;
	return (wait_for_heredoc_child(pid)); // exit code or (128+sig)
}

static void	handle_heredoc_child(t_shell *shell, t_dir *redir)
{
	char	*line;
	bool	is_quoted;

	close(redir->heredoc_fd[READ_END]);
	is_quoted = does_included_quote(redir->filename);
	redir->filename = remove_quotes_update_str(shell, redir->filename);
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
			break;
		if (are_strs_equal(line, redir->filename))
		{
			free(line);
			break;
		}
		line = update_heredoc_prompt(shell, is_quoted, line);
		ft_putendl_fd(line, redir->heredoc_fd[WRITE_END]);
		free(line);
	}
	close(redir->heredoc_fd[WRITE_END]);
	if (!line)
		eof_msg(shell, redir->filename);
	shut_program(shell, false, EX_OK);    // Delimiter matched, also Ctrl+D treated as success
}

// * Handles the child process for reading and writing heredoc input
static int wait_for_heredoc_child(pid_t pid)
{
	int	status;
	int	signal_num;
	int	exit_code;

	exit_code = EX_KO;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		return (exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
		return (128 + signal_num);
	}
	return (exit_code); // Undefined behavior, should not happen!
}

// * Waits for the heredoc child process to finish and returns the exit status or signal
static char *update_heredoc_prompt(t_shell *shell, bool is_quoted, char *line)
{
	char  *temp;

	if (is_quoted)
	{
		return (line);
	}
	temp = expand_vars(shell, line);
	if (!temp)
	{
		temp = ft_strdup("");
		if (!temp)
		{
			shut_program(shell, true, EX_KO);
			return (NULL);
		}
		return (temp);
	}
	return (temp);
}
