#include "minishell.h"

static pid_t execute_cmd(t_shell *shell, t_cmd *cmd, int index);
static pid_t fork_and_execute(t_shell *shell, t_cmd *cmd, int index);
static void parent_wait(t_shell *shell, pid_t last_pid);

void execution(t_shell *shell)
{
    pid_t last_pid;
    t_cmd *cmd;
    int i;

    last_pid = -1;
    cmd = shell->cmd;
    i = 0;
    while (cmd)
    {
        if (!setup_redirections_with_pipe(shell, cmd, i))
        {
            cmd = cmd->next;
            i++;
            continue;
        }
        last_pid = execute_cmd(shell, cmd, i);
        cmd = cmd->next;
        i++;
    }
    parent_wait(shell, last_pid);
}

static pid_t execute_cmd(t_shell *shell, t_cmd *cmd, int index)
{
    if (is_builtin(cmd->args) && shell->num_pipes == 0)
    {
        shell->cur_exit_flag = execute_builtin(shell, cmd);
        return (-1);
    }
    return (fork_and_execute(shell, cmd, index));
}

static pid_t fork_and_execute(t_shell *shell, t_cmd *cmd, int index)
{
    pid_t pid;
    int **pipes = shell->num_pipes_fd;

    pid = fork();
    if (pid < 0)
        shut_program(shell, true, EX_KO);
    if (pid == 0)
        child_process(shell, cmd, index);
    else
    {
        if (index > 0 && pipes[index - 1][0] >= 0)
        {
            close(pipes[index - 1][0]);
            pipes[index - 1][0] = -1;
        }
        if (index < shell->num_pipes && pipes[index][1] >= 0)
        {
            close(pipes[index][1]);
            pipes[index][1] = -1;
        }
    }
    return (pid);
}

static void	parent_wait(t_shell *shell, pid_t last_pid)
{
	pid_t	pid;
	int		status;

	close_all_pipes(shell);
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->cur_exit_flag = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->cur_exit_flag = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
	close_redirections(shell->cmd);
}

