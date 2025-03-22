#include "minishell.h"

static int **allocate_pipes(int num_pipes)
{
	int	i;
	int	**pipe_fd;

	pipe_fd = malloc(sizeof(int *) * (num_pipes + 1));
	if (!pipe_fd)
		handle_error("Memory allocation failed for pipes", EX_KO);

    i = 0;
    while (i <= num_pipes)
    {
        pipe_fd[i] = malloc(sizeof(int) * 2);
        if (!pipe_fd[i])
            handle_error("Memory allocation failed for pipe pair", EX_KO);
        i++;
    }
    return (pipe_fd);
}

static void create_pipes(t_shell *shell, t_cmd *cmd, int **pipe_fd, int num_pipes)
{
	(void)shell; // TODO: Use this for error handling later
	int i;

	i = 0;
    while (num_pipes)
    {
    	// Create the pipe between the current and next command
    	pipe(pipe_fd[i]);
        
		// Set the current command's output fd
    	cmd->out_fd = pipe_fd[i][1];

		// Set the next command's input fd (if any?)
    	if (cmd->next)
			cmd->next->in_fd = pipe_fd[i][0];
    	i++;
    }
}

int	**handle_pipe(t_shell *shell, t_cmd *cmd, int num_pipes)
{
	int	**pipe_fd;

	// Allocate memory for the pipes
	pipe_fd = allocate_pipes(num_pipes);
	
	// Create the pipes and set the file descriptors
	create_pipes(shell, cmd, pipe_fd, num_pipes);

	// // Close and clean up the pipes
    // close_pipes(pipe_fd, num_pipes); // Should we do this in the parent process instead?
	return (pipe_fd);
}
