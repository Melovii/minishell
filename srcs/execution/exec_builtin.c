#include "minishell.h"
#include "../libft/libft.h"

static int run_builtin(t_shell *shell, t_cmd *cmd);

bool	is_builtin(t_token *token_lst)
{
	char *cmd;

	if (!token_lst)
		return (false);
	cmd = token_lst->value;
	if (are_strs_equal(cmd, "echo")
		|| are_strs_equal(cmd, "cd")
		|| are_strs_equal(cmd, "pwd")
		|| are_strs_equal(cmd, "export")
		|| are_strs_equal(cmd, "unset")
		|| are_strs_equal(cmd, "env")
		|| are_strs_equal(cmd, "exit"))
		return (true);
	return (false);
}

int	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	int	original_stdin;
	int	original_stdout;
    int exit_status;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (cmd->in_fd != STDIN_FILENO)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	if (cmd->out_fd != STDOUT_FILENO)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
	exit_status = run_builtin(shell, cmd);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
    return (exit_status);
}

static int	run_builtin(t_shell *shell, t_cmd *cmd)
{
	char	**args;
	int		status;

	args = modify_args(cmd);
	if (!args)
		return (1);
	if (are_strs_equal(cmd->args->value, "echo"))
		status = ft_echo(args);
	else if (are_strs_equal(cmd->args->value, "cd"))
		status = ft_cd(shell, args);
	else if (are_strs_equal(cmd->args->value, "pwd"))
		status = ft_pwd(shell);
	else if (are_strs_equal(cmd->args->value, "export"))
		status = ft_export(shell, args);
	else if (are_strs_equal(cmd->args->value, "unset"))
		status = ft_unset(shell, args);
	else if (are_strs_equal(cmd->args->value, "env"))
		status = ft_env(shell, false);
	else if (are_strs_equal(cmd->args->value, "exit"))
		status = ft_exit(shell, args);
	else
		status = 1;
	ft_free_tab(args);
	return (status);
}


char	**modify_args(t_cmd *cmd)
{
	char	**args;
	t_token	*tmp;
	int		i;
	int		count;

	count = get_len_cmd_args(cmd);
	args = ft_calloc(count + 1, sizeof(char *));
	if (!args)
		return (NULL);
	tmp = cmd->args;
	i = 0;
	while (tmp)
	{
		args[i] = ft_strdup(tmp->value);
		if (!args[i])
		{
			ft_free_tab(args); // helper to free allocated strings
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	return (args);
}

