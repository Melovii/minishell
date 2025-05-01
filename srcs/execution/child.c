#include "minishell.h"
#include "../libft/libft.h"

static void	resolve_cmd_and_args(t_shell *shell, t_cmd *cmd, char **path, char ***args);
static void	setup_child(t_cmd *cmd, t_shell *shell, int i);
static void	child_cleanup_and_exit(t_shell *shell, t_cmd *cmd, int i, int code);
static void	execute_resolved_cmd(t_shell *shell, char *path, char **args);

void	child_process(t_shell *shell, t_cmd *cmd, int i)
{
	char	*path;
	char	**args;

	if (cmd->args == NULL)
		child_cleanup_and_exit(shell, cmd, i, 0);
	if (are_strs_equal(cmd->args->value, ""))
	{
		ft_putendl_fd("minishell: command not found: ''", STDERR_FILENO);
		child_cleanup_and_exit(shell, cmd, i, 127);
	}
	setup_child(cmd, shell, i);
	resolve_cmd_and_args(shell, cmd, &path, &args);
	if (cmd_is_dir(path))
	{
		print_dir_error(path);
		free(path);
		shut_program(shell, false, 126);
	}
	execute_resolved_cmd(shell, path, args);
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

static void	child_cleanup_and_exit(t_shell *shell, t_cmd *cmd, int i, int code)
{
	close_unused_pipes(shell, i);
	close_redirections(cmd);
	shut_program(shell, false, code);
}

static void	execute_resolved_cmd(t_shell *shell, char *path, char **args)
{
	execve(path, args, shell->og_env);
	free(path);
	ft_free_tab(args);
	shut_program(shell, true, 127);
}
