#include "minishell.h"

// * Function to open a file for reading or writing
int	ft_open_file(char *file_name, int flow)
{
	int	fd;

	if (flow)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(file_name, O_RDONLY, 0777);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(file_name);
		return (-1);
	}
	return (fd);
}

// * Function to find the PATH in the environment variables
char	*ft_find_envp(char **envp)
{
	int		i;
	char	*envp_path;

	i = 0;
	envp_path = NULL; // Initialize to NULL
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!envp_path) // If PATH is not found
		exit(EXIT_FAILURE);
	return (envp_path);
}


// * Function to find the command in the PATH
char	*ft_find_cmd(char *cmd, char **envp)
{
	char	**cmd_options;
	char	**path;
	char	*path_part;
	char	*exec;
	int		index;

	index = -1;
	path = ft_split(ft_find_envp(envp), ':');
	cmd_options = ft_split(cmd, ' ');
	while (path[++index])
	{
		path_part = ft_strjoin(path[index], "/");
		exec = ft_strjoin(path_part, cmd_options[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(cmd_options);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(path);
	ft_free_tab(cmd_options);
	return (cmd);
}
