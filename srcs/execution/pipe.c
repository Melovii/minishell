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
    (void)shell; // For future error handling
    int i;

	i = 0;
    while (i < num_pipes && cmd -> next)
    {
        // Create a pipe between the current command and the next command
        if (pipe(pipe_fd[i]) == -1)
            handle_error("pipe() function error", EX_KO); // ! check later
        
        // Assign the current command's output file descriptor to the write end of the pipe
        cmd->out_fd = pipe_fd[i][1];

        // If there is a next command, assign its input file descriptor to the read end of the pipe
        if (cmd->next)
        {
            cmd->next->in_fd = pipe_fd[i][0];
            cmd = cmd->next; // Move to the next command in the linked list
			i++;
        }
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
