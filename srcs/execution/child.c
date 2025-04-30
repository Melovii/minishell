#include "minishell.h"
#include "../libft/libft.h"

static void	resolve_cmd_and_args(t_shell *shell, t_cmd *cmd, char **path, char ***args);
static void	setup_child(t_cmd *cmd, t_shell *shell, int i);

void	child_process(t_shell *shell, t_cmd *cmd, int i)
{
	char	*path;
	char	**args;

	if (are_strs_equal("", cmd->args->value))
	{
		ft_putendl_fd("minishell: command not found: ''", STDERR_FILENO);
		shut_program(shell, false, 127);
	}
	setup_child(cmd, shell, i);
	resolve_cmd_and_args(shell, cmd, &path, &args);
	if (cmd_is_dir(path))
	{
		print_dir_error(path);
		free(path);
		shut_program(shell, false, 126);
	}
	execve(path, args, shell->og_env); // ? Does this need if condition?
	shut_program(shell, true , 127); // ? Check if exit code is correct?
}

static void	setup_child(t_cmd *cmd, t_shell *shell, int i)
{
	if (cmd->in_fd != STDIN_FILENO)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
		if (has_input_redirection_via_list(cmd) && i > 0)
        {
			close(shell->num_pipes_fd[i - 1][0]);
            shell->num_pipes_fd[i - 1][0] = -1;
        }
	}
	if (cmd->out_fd != STDOUT_FILENO)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
		if (has_output_redirection_via_list(cmd) && i < shell->num_pipes)
        {
			close(shell->num_pipes_fd[i][1]);
            shell->num_pipes_fd[i][1] = -1;
        }
	}
	close_unused_pipes(shell, i);
}


static void	resolve_cmd_and_args(t_shell *shell, t_cmd *cmd, char **path, char ***args)
{
	*path = get_cmd_path(shell, cmd->args->value, &(shell->cur_exit_flag));
	if (!(*path))
	{
		shut_program(shell, false, shell->cur_exit_flag);
	}
	*args = modify_args(cmd);
	if (!*args)
	{
		free(*path);
		shut_program(shell, true, 1);
	}
}

void	close_unused_pipes(t_shell *shell, int current)
{
	int	i;

	i = 0;
    if (!shell->num_pipes_fd)
        return ;
	while (i < shell->num_pipes)
	{
		if (i != current && shell->num_pipes_fd[i][1] != -1)
        {
			close(shell->num_pipes_fd[i][1]);
            shell->num_pipes_fd[i][1] = -1;
        }
		if (i != current - 1 && shell->num_pipes_fd[i][0] != -1)
        {
			close(shell->num_pipes_fd[i][0]);
            shell->num_pipes_fd[i][0] = -1;
        }
		i++;
	}
}

