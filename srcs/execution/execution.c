#include "minishell.h"

static pid_t	execute_cmd(t_shell *shell, t_cmd *cmd, int index);
static pid_t	fork_and_execute(t_shell *shell, t_cmd *cmd, int index);
static void		close_unused_pipe_ends(t_shell *shell, int index);
static void		parent_wait(t_shell *shell, pid_t last_pid);

// * Executes the command and handles the redirections and pipe setup
void	execution(t_shell *shell)
{
	pid_t	last_pid;
	t_cmd	*cmd;
	int		i;

	last_pid = -1;
	cmd = shell->cmd;
	i = 0;
	while (cmd)
	{
		if (!setup_redirections_with_pipe(shell, cmd, i))
		{
			last_pid = -1;
			shell->cur_exit_flag = 1;
			i++;
			cmd = cmd->next;
			continue ;
		}
		last_pid = execute_cmd(shell, cmd, i);
		cmd = cmd->next;
		i++;
	}
	parent_wait(shell, last_pid);
}

// * Executes the command, either as a built-in or by forking a process
static pid_t	execute_cmd(t_shell *shell, t_cmd *cmd, int index)
{
	if ((is_builtin(cmd->args) && shell->num_pipes == 0))
	{
		shell->cur_exit_flag = execute_builtin(shell, cmd);
		return (-1);
	}
	return (fork_and_execute(shell, cmd, index));
}

// * Forks a new process and executes the command in the child process
static pid_t	fork_and_execute(t_shell *shell, t_cmd *cmd, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		shut_program(shell, true, EX_KO);
	if (pid == 0)
	{
		handle_signals(EXEC_CMD);
		child_process(shell, cmd, index);
	}
	else
	{
		close_unused_pipe_ends(shell, index);
	}
	return (pid);
}

// * Closes unused pipe ends in the parent process to avoid file descriptor leaks.
static void	close_unused_pipe_ends(t_shell *shell, int index)
{
	int	**pipes;

	pipes = shell->num_pipes_fd;
	pipes = shell->num_pipes_fd;
	if (index > 0 && pipes[index - 1][READ_END] >= 2)
	{
		close(pipes[index - 1][READ_END]);
		pipes[index - 1][READ_END] = -1;
	}
	if (index < shell->num_pipes && pipes[index][WRITE_END] >= 0)
	{
		close(pipes[index][WRITE_END]);
		pipes[index][WRITE_END] = -1;
	}
}

// * Waits for the child process to finish and handles exit status
static void	parent_wait(t_shell *shell, pid_t last_pid)
{
	pid_t	pid;
	int		status;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->cur_exit_flag = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->cur_exit_flag = 128 + WTERMSIG(status);
			if (shell->cur_exit_flag == 130)
				handle_sigint_output();
		}
		pid = wait(&status);
	}
	close_all_pipes(shell);
	close_redirections(shell->cmd);
}
