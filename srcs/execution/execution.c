#include "minishell.h"

static void	execute_cmd(t_shell *shell, t_cmd *cmd, int i);
static void	wait_all_children(t_shell *shell);
static void	close_all_pipes(t_shell *shell);
static void	close_all_redirections(t_cmd *cmd_list);

void	execution(t_shell *shell)
{
	t_cmd	*cmd;
	int		i;

	cmd = shell->cmd;
	shell->num_pipes_fd = setup_pipes(shell, shell->num_pipes);
	i = 0;
    shell->exit_flag = process_heredocs(shell); // ! Check (exit code + signal handling) out
    if (shell->exit_flag != EX_OK)
        return ;
    while (cmd)
    {
        if (!setup_redirections_with_pipe(shell, cmd, i))
        {
            cmd = cmd->next;
            i++;
            continue;
        }
        execute_cmd(shell, cmd, i);
        cmd = cmd->next;
        i++;
    }
    close_all_pipes(shell);
    close_all_redirections(shell->cmd);
	wait_all_children(shell);
}

static void	execute_cmd(t_shell *shell, t_cmd *cmd, int i)
{
	pid_t	pid;

	if (is_builtin(cmd->args->value))
	{
		shell->exit_flag = execute_builtin(shell, cmd);
	}
    else
    {
        pid = fork();
        if (pid < 0)
            shut_program(shell, true, EX_KO);
        else if (pid == 0)
            child_process(shell, cmd, i);
    }
}

static void	wait_all_children(t_shell *shell)
{
	int	status;
	int	last_exit;

	last_exit = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_exit = (128 + WTERMSIG(status));
	}
	shell->exit_flag = last_exit;
}

static void	close_all_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->num_pipes)
	{
		if (shell->num_pipes_fd[i][0] != -1)
		{
			close(shell->num_pipes_fd[i][0]);
			shell->num_pipes_fd[i][0] = -1;
		}
		if (shell->num_pipes_fd[i][1] != -1)
		{
			close(shell->num_pipes_fd[i][1]);
			shell->num_pipes_fd[i][1] = -1;
		}
		i++;
	}
}

static void	close_all_redirections(t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		if (has_input_redirection_via_list(cmd)
			&& cmd->in_fd != -1 && cmd->in_fd != STDIN_FILENO)
		{
			close(cmd->in_fd);
			cmd->in_fd = -1;
		}
		if (has_output_redirection_via_list(cmd)
			&& cmd->out_fd != -1 && cmd->out_fd != STDOUT_FILENO)
		{
			close(cmd->out_fd);
			cmd->out_fd = -1;
		}
		cmd = cmd->next;
	}
}
