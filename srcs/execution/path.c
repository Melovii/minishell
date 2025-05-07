#include "minishell.h"

static bool unset_path_case(char **paths, int *exit_code, int *flag);
static char	*check_single_path(t_shell *shell, char *dir, char *cmd, int *exit_code);
static char	*check_direct_path(char *cmd, int *exit_code);
static char	*search_command_in_path(t_shell *shell, char *cmd, int *exit_code, int *flag);

// * Main function to get the full path of a command
char	*get_cmd_path(t_shell *shell, char *cmd, int *exit_code)
{
	char *path;
	int	flag;

	flag = 0;
	if (ft_strchr(cmd, '/'))
		return (check_direct_path(cmd, exit_code));
	else
	{
		path = search_command_in_path(shell, cmd, exit_code, &flag);
		if (!path && flag)
		{
			path_error_msg(cmd, NOT_FOUND, false);
			return (NULL);
		}
		return (path);
	}
}

// * Check if the command has a direct path and whether it is accessible
static char	*check_direct_path(char *cmd, int *exit_code)
{
	if (access(cmd, F_OK) != 0)
	{
		*exit_code = NOT_FOUND;
        path_error_msg(cmd, *exit_code, true);
		return (NULL);
	}
	if (access(cmd, X_OK) != 0)
	{
		*exit_code = NO_PERM;
        path_error_msg(cmd, *exit_code, true);
		return (NULL);
	}
	*exit_code = 0;
	return (ft_strdup(cmd));
}

// * Search for the command in the directories listed in PATH
static char	*search_command_in_path(t_shell *shell, char *cmd, int *exit_code, int *flag)
{
	char	**paths;
	char	*result;
	int		i;
	int		final_exit;

	paths = get_paths_array(shell);
	if (unset_path_case(paths, exit_code, flag))
		return (NULL);
	i = -1;
	final_exit = NOT_FOUND;
	while (paths[++i])
	{
		result = check_single_path(shell, paths[i], cmd, exit_code);
		if (result)
		{
			ft_free_tab(paths);
			return (result);
		}
		if (*exit_code == NO_PERM)
			final_exit = NO_PERM;
	}
	ft_free_tab(paths);
	*exit_code = final_exit;
	path_error_msg(cmd, *exit_code, false);
	return (NULL);
}

// * Handle the case where there are no paths in the PATH variable
static bool unset_path_case(char **paths, int *exit_code, int *flag)
{
	if (!paths)
	{
		*flag = 1;
		*exit_code = NOT_FOUND;
		return (true);
	}
	return (false);
}

// * Check if the command exists in a single directory and if it's executable
static char	*check_single_path(t_shell *shell, char *dir, char *cmd, int *exit_code)
{
	char	*full_path;

	full_path = ft_strjoin_path(dir, cmd);
	if (!full_path)
	{
		*exit_code = 1;
		shut_program(shell, true, *exit_code);
		return (NULL);
	}
	if (access(full_path, F_OK) == 0)
	{
		if (access(full_path, X_OK) == 0)
		{
			*exit_code = 0;
			return (full_path);
		}
		*exit_code = NO_PERM;
	}
	else
		*exit_code = NOT_FOUND;
	free(full_path);
	return (NULL);
}
