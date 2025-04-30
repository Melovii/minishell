#include "minishell.h"

static pid_t execute_cmd(t_shell *shell, t_cmd *cmd, int index);
static pid_t fork_and_execute(t_shell *shell, t_cmd *cmd, int index);
static void close_all_pipes(t_shell *shell);
static void close_redirections(t_cmd *cmd_list);
static void parent_wait(t_shell *shell, pid_t last_pid);

// Main execution entry
void execution(t_shell *shell)
{
	pid_t last_pid = -1;
	t_cmd *cmd = shell->cmd;
	int i = 0;

	while (cmd)
	{
		last_pid = execute_cmd(shell, cmd, i);
		cmd = cmd->next;
		i++;
	}
	parent_wait(shell, last_pid);
}

// Dispatch command: builtin or fork
static pid_t execute_cmd(t_shell *shell, t_cmd *cmd, int index)
{
	if (is_builtin(cmd->args->value) && shell->num_pipes == 0)
	{
		shell->cur_exit_flag = execute_builtin(shell, cmd);
		return (-1);
	}
	return (fork_and_execute(shell, cmd, index));
}

// Fork child and manage pipes
static pid_t fork_and_execute(t_shell *shell, t_cmd *cmd, int index)
{
	pid_t pid = fork();

	if (pid < 0)
		shut_program(shell, true, EX_KO);
	if (pid == 0)
	{
		if (!setup_redirections_with_pipe(shell, cmd, index))
		{
			close_all_pipes(shell);
			exit(1);
		}
		child_process(shell, cmd, index);
	}
	else
		close_unused_pipes(shell, index);
	return (pid);
}


// Close any remaining pipe fds
static void close_all_pipes(t_shell *shell)
{
	if (!shell->num_pipes_fd)
		return;

	int i = 0;
	while (i < shell->num_pipes)
	{
		if (shell->num_pipes_fd[i][0] >= 0)
			close(shell->num_pipes_fd[i][0]);
		if (shell->num_pipes_fd[i][1] >= 0)
			close(shell->num_pipes_fd[i][1]);
		i++;
	}
}

// Close redirection fds for each command node
static void close_redirections(t_cmd *cmd_list)
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

static void parent_wait(t_shell *shell, pid_t last_pid)
{
	int status;
	close_all_pipes(shell);
	if (last_pid > 0)
	{
		if (waitpid(last_pid, &status, 0) == -1)
			shut_program(shell, true, EX_KO);
		if (WIFEXITED(status))
			shell->cur_exit_flag = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGPIPE)
				shell->cur_exit_flag = 0;
			else
				shell->cur_exit_flag = 128 + sig;
		}
		while (wait(NULL) > 0)
			;
	}
	close_redirections(shell->cmd);
}
