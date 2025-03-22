#include "minishell.h"

static void	child_prc(char **args)
{
	// TODO: Consider using t_shell for the file descriptors
	int fd_in;
	int	fd_out;
	
	fd_in = -1;
	fd_out = -1;

    handle_redirection(args, &fd_in, &fd_out);

	// TODO: Add the path of the command from t_shell later (or somewhere...)

	// ! USE THE UTILS FOR PATH FINDING AND USE ACCESS() TO CHECK PERMISSION
	if (execve(path, args, NULL) == -1)
		handle_error("Execve failed", EX_KO);

	// TODO: Check where to close these
	if (fd_in != -1)
		close(fd_in);
	if (fd_in != -1)
		close(fd_in);
}

// TODO: Consider changing g_received_signal based on code
static void	parent_prc(pid_t pid)
{
	int		status;
	pid_t	wpid;

	waitpid(pid, &status, 0); // Wait for the child to finish
	if (wpid == -1)
		handle_error("Error waiting for child", EX_KO);
	
	if (WIFEXITED(status)) // Check if child was terminated normally
		printf("Child exited with the status %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status)) // Check if child was terminated by signal
		printf("Child process terminated by signal %d\n", WTERMSIG(status));
}

int exec_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		num_pipes;
	int		**pipe_fd;

	if (is_builtin(cmd->args[0]))
		return (exec_builtin(shell, cmd));

	pipe_fd = handle_pipe(shell, cmd, count_pipes(num_pipes));
	pid = fork();
	if (pid < 0)
		handle_error("Error forking", EX_KO);
	else if (pid == 0) // Child Process (exec cmd here)
		child_prc(args);
	else
		parent_prc(pid); // Parent Process (waitpid here)

	// Close and clean up the pipes
    close_pipes(pipe_fd, num_pipes);
	// TODO: Check if we need an extra pipe closing function for SIGNALS
	return (EX_OK);
}
