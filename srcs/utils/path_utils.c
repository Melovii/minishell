#include "minishell.h"

static void	print_exec_errors(char *cmd, bool is_command, bool does_exist);
static char	*find_relative_helper(char *exec, char **path_dirs);
static char *get_path_if_exist(char **path_dirs, char *cmd, int i);
static char	*find_relative(t_shell *shell, char *cmd);
static char	*find_absolute(char *cmd);

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

char	*ft_find_cmd(t_shell *shell, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		return (find_absolute(cmd));
	}
	return (find_relative(shell, cmd));
}

static char	*find_relative(t_shell *shell, char *cmd)
{
	char	**path_dirs;
	char	*cmd_path;
	char	*path_value;
	int		i;

	path_value = get_env_value(shell->env, "PATH");
	if (!path_value)
	{
		print_exec_errors(cmd, true, false);
		return (NULL);
	}
	path_dirs = ft_split(get_env_value(shell->env, "PATH"), ':');
	if (!path_dirs)
		handle_error("Alloc Error on ft_find_relative()", EX_KO);
	i = -1;
	while (path_dirs[++i])
	{
		cmd_path = get_path_if_exist(path_dirs, cmd, i);
		if (cmd_path)
			return (cmd_path);
	}
	ft_free_tab(path_dirs);
	print_exec_errors(cmd, true, false); // command not found
	return (NULL);
}

static char *get_path_if_exist(char **path_dirs, char *cmd, int i)
{
	char *temp;
	char *exec;

	temp = ft_strjoin(path_dirs[i], "/");
	if (!temp)
	{
		ft_free_tab(path_dirs);
		handle_error("Alloc Error on get_path_if_exist()", EX_KO);
	}
	exec = ft_strjoin(temp, cmd);
	free(temp);
	if (!exec)
	{
		ft_free_tab(path_dirs);
		handle_error("Alloc Error on get_path_if_exist()", EX_KO);
	}
	if (access(exec, F_OK) == 0)
		return (find_relative_helper(exec, path_dirs));
	free(exec);
	return (NULL);
}

static char	*find_relative_helper(char *exec, char **path_dirs)
{
	ft_free_tab(path_dirs);
	if (access(exec, X_OK) == 0)
	{
		return (exec);
	}
	else
	{
		print_exec_errors(exec, true, true);
		free(exec);
		return (NULL);
	}
}

static char	*find_absolute(char *cmd)
{
	printf("it works\n");
	if (access(cmd, F_OK) != 0)
	{
		print_exec_errors(cmd, false, false);
		return (NULL);
	}
	if (access(cmd, X_OK) != 0)
	{
		print_exec_errors(cmd, false, true);
		return (NULL);
	}
	return (ft_strdup(cmd));
}

static void	print_exec_errors(char *cmd, bool is_command, bool does_exist)
{
	if (does_exist)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putendl_fd(cmd, 2);
	}
	else if (!(is_command))
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putendl_fd(cmd, 2);
	}
	else if (is_command)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
	}
}
