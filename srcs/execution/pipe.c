#include "minishell.h"
#include "../libft/libft.h"

static int	**allocate_pipe_fd(t_shell *shell, int num_pipes);
static int	open_pipes(int **pipe_fd, int num_pipes);

int     count_pipes(t_cmd *cmd)
{
    int count;

    count = 0;
    while (cmd)
    {
        if (cmd->next)
            count++;
        cmd = cmd->next;
    }
    printf("Number of pipes: %d\n", count); // ! Debugging line
    return (count);
}

void	free_pipe_fd(int **pipe_fd, int num)
{
	int	i;

	if (!pipe_fd)
		return ;
	i = 0;
	while (i < num)
	{
		if (pipe_fd[i])
		{
			if (pipe_fd[i][0] != -1)
				close(pipe_fd[i][0]);
			if (pipe_fd[i][1] != -1)
				close(pipe_fd[i][1]);
			free(pipe_fd[i]);
		}
		i++;
	}
	free(pipe_fd);
}

int	**setup_pipes(t_shell *shell, int num_pipes)
{
	int	**pipe_fd;

	pipe_fd = allocate_pipe_fd(shell, num_pipes);
	if (!pipe_fd)
		shut_program(shell, true, EX_KO);
	if (open_pipes(pipe_fd, num_pipes) == -1)
	{
		shut_program(shell, true, EX_KO);
	}
	return (pipe_fd);
}

static int	**allocate_pipe_fd(t_shell *shell, int num_pipes)
{
	int	**pipe_fd;
	int	i;

	pipe_fd = ft_calloc(num_pipes, sizeof(int *));
	if (!pipe_fd)
		return (NULL);
	i = 0;
	while (i < num_pipes)
	{
		pipe_fd[i] = ft_calloc(PIPE_PAIR, sizeof(int));
		if (!pipe_fd[i])
		{
			free_pipe_fd(pipe_fd, i);
			shut_program(shell, true, EX_KO);
		}
        pipe_fd[i][0] = -1;
        pipe_fd[i][1] = -1;
		i++;
	}
	return (pipe_fd);
}

static int	open_pipes(int **pipe_fd, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipe_fd[i]) == -1)
		{
			free_pipe_fd(pipe_fd, i);
			return (-1);
		}
		i++;
	}
	return (0);
}
