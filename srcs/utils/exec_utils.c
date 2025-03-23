#include "minishell.h"

int	count_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	// printf("Number of pipes: %d\n", i - 1);
	return (i - 1);
}

void close_pipes(int **pipe_fd, int num_pipes)
{
    int i;

    i = 0;
    while (i <= num_pipes)
    {
        close(pipe_fd[i][0]);
        close(pipe_fd[i][1]);
        free(pipe_fd[i]);  // Free each pipe pair (each array of 2 integers)
        i++;
    }
    free(pipe_fd);  // Free the array of pipes
}
