
#include "minishell.h"

char	*ft_strjoin_path(char *dir, char *cmd)
{
	char	*joined;
	char	*temp;

	if (!dir || !cmd)
		return (NULL);
	if (dir[ft_strlen(dir) - 1] == '/')
		return (ft_strjoin(dir, cmd));
	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	joined = ft_strjoin(temp, cmd);
	free(temp);
	return (joined);
}

// * Checks if the command is a directory rather than an executable.
bool	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode)); // * True if the command is a directory
}

char	**get_paths_array(t_shell *shell)
{
	char	*path_env;

	path_env = get_env_value(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	return (ft_split(path_env, ':'));
}
