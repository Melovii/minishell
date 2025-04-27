#include "minishell.h"
#include "../libft/libft.h"

static char	*check_single_path(t_shell *shell, char *dir, char *cmd, int *exit_code);
static char	**get_paths_array(t_shell *shell);
static char	*check_direct_path(char *cmd, int *exit_code);
static char	*search_command_in_path(t_shell *shell, char *cmd, int *exit_code);

char	*get_cmd_path(t_shell *shell, char *cmd, int *exit_code)
{
	if (ft_strchr(cmd, '/'))
		return (check_direct_path(cmd, exit_code));
	else
		return (search_command_in_path(shell, cmd, exit_code));
}

static char	*check_direct_path(char *cmd, int *exit_code)
{
	if (access(cmd, F_OK) != 0)
	{
		*exit_code = 127;
        path_error_msg(cmd, *exit_code, true);
		return (NULL);
	}
	if (access(cmd, X_OK) != 0)
	{
		*exit_code = 126;
        path_error_msg(cmd, *exit_code, true);
		return (NULL);
	}
	*exit_code = 0;
	return (ft_strdup(cmd));
}

char	*search_command_in_path(t_shell *shell, char *cmd, int *exit_code)
{
	char	**paths;
	char	*result;
	int		i;
	int		final_exit;

	paths = get_paths_array(shell);
	if (!paths)
		return (NULL);
	i = -1;
	final_exit = 127;
	while (paths[++i])
	{
		result = check_single_path(shell, paths[i], cmd, exit_code);
		if (result)
		{
			ft_free_tab(paths);
			return (result);
		}
		if (*exit_code == 126)
			final_exit = 126;
	}
	ft_free_tab(paths);
	*exit_code = final_exit;
	path_error_msg(cmd, *exit_code, false);
	return (NULL);
}

static char	**get_paths_array(t_shell *shell)
{
	char	*path_env;

	path_env = get_env_value(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	return (ft_split(path_env, ':'));
}

static char	*check_single_path(t_shell *shell, char *dir, char *cmd, int *exit_code)
{
	char	*full_path;

	full_path = ft_strjoin_path(dir, cmd);
	if (!full_path)
	{
		*exit_code = 1;
		shut_program(shell, "Memory allocation error on check_single_path()", *exit_code);
		return (NULL);
	}
	if (access(full_path, F_OK) == 0)
	{
		if (access(full_path, X_OK) == 0)
		{
			*exit_code = 0;
			return (full_path);
		}
		*exit_code = 126;
	}
	else
		*exit_code = 127;
	free(full_path);
	return (NULL);
}
