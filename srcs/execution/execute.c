#include "minishell.h"

static void close_unused_pipes(int **pipe_fd, int num_pipes, int i, int is_child)
{
    int j;

	j = 0;
    if (is_child)
    {
        // Close all pipes except necessary ones for child process
        while (j < num_pipes)
        {
            if (j != i - 1) // Keep read-end of previous pipe open
                close(pipe_fd[j][0]);
            if (j != i) // Keep write-end of current pipe open
                close(pipe_fd[j][1]);
            j++;
        }
    }
    else
    {
        j = 0;
        // Parent closes all pipe ends after forking
        while (j < num_pipes)
        {
            close(pipe_fd[j][0]);
            close(pipe_fd[j][1]);
            j++;
        }
    }
}


static void child_prc(t_shell *shell, t_cmd *cmd, int **pipe_fd, int i)
{
	char	*path;

    if (cmd->in_fd != STDIN_FILENO) // Set up input redirection
    {
        dup2(cmd->in_fd, STDIN_FILENO);
        close(cmd->in_fd);
    }
    else if (i > 0) // Read from previous pipe
        dup2(pipe_fd[i - 1][0], STDIN_FILENO);

    if (cmd->out_fd != STDOUT_FILENO) // Set up output redirection
    {
        dup2(cmd->out_fd, STDOUT_FILENO);
        close(cmd->out_fd);
    }
    else if (i < shell->num_pipes) // Write to next pipe
        dup2(pipe_fd[i][1], STDOUT_FILENO);

    close_unused_pipes(pipe_fd, shell->num_pipes, i, 1);
	path = ft_find_cmd(shell, cmd->args[0]);
	if (!path)
		exit (127); // ! CHECK LATER POTENTIAL LEAK
	if (execve(path, &cmd->args[0], shell->og_env) == -1) // Execute command
		handle_error("Execve failed", EX_KO);
}

static void parent_prc(pid_t pid)
{
    int status;

    if (waitpid(pid, &status, 0) == -1)
        perror("Error waiting for child");
    if (WIFEXITED(status))
        printf("Child exited with status %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("Child process terminated by signal %d\n", WTERMSIG(status));
}

int exec_cmd(t_shell *shell, t_cmd *cmd)
{
    pid_t pid;
    int **pipe_fd;
    int i;
	int	builtin_status;

    shell->num_pipes = count_pipes(cmd);
    pipe_fd = handle_pipe(shell, cmd, shell->num_pipes);
	i = 0;
    while (cmd)
    {
		// TODO: Consider removing the builtin status or the is_builtin function
		if (is_builtin(cmd->args[0]))
		{
			builtin_status = exec_builtin(shell, cmd->args);
			if (builtin_status != -1)
			{
				cmd = cmd->next;
				i++;
				continue;
			}
		}
        pid = fork();
        if (pid < 0)
            handle_error("Error forking", EXIT_FAILURE);
        else if (pid == 0)  // Child process
            child_prc(shell, cmd, pipe_fd, i);

        cmd = cmd->next;
        i++;
    }

    close_unused_pipes(pipe_fd, shell->num_pipes, i, 0);

    // Wait for all child processes
	while (i-- > 0)
		parent_prc(pid);

    return (1);
}
