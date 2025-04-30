#include "minishell.h"
#include "../libft/libft.h"

static int	do_cd(t_shell *shell, char **args);
static char	*get_oldpwd_or_error(void);
static int	change_directory(t_shell *shell, char **args, char **target, bool *print_path);
static char	*get_cd_target(char **args, t_env *env, bool *print_path);
static int	update_pwd_vars(t_shell *shell, char *oldpwd);

// * Main cd function
int	ft_cd(t_shell *shell, char **args)
{
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (do_cd(shell, args));
}

// * Perform cd logic
static int	do_cd(t_shell *shell, char **args)
{
	char	*oldpwd;
	char	*target;
	bool	print_path;

	oldpwd = get_oldpwd_or_error();
	if (!oldpwd)
		return (1);
	if (change_directory(shell, args, &target, &print_path))
	{
		free(oldpwd);
		return (1);
	}
	if (print_path)
		ft_putendl_fd(target, STDOUT_FILENO);
	if (update_pwd_vars(shell, oldpwd))
	{
		ft_putendl_fd("minishell: cd: failed to update PWD", STDERR_FILENO);
		free(oldpwd);
		return (1);
	}
	free(oldpwd);
	return (0);
}

// * Retrieve old working directory
static char	*get_oldpwd_or_error(void)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		ft_putendl_fd("minishell: cd: getcwd error", STDERR_FILENO);
	return (oldpwd);
}

// * Change to target directory
static int	change_directory(t_shell *shell, char **args, char **target, bool *print_path)
{
	*print_path = false;
	*target = get_cd_target(args, shell->env, print_path);
	if (!*target)
		return (1);
	if (chdir(*target) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(*target);
		return (1);
	}
	return (0);
}

// * Determine target path for cd
static char	*get_cd_target(char **args, t_env *env, bool *print_path)
{
	char	*val;

	if (!args[1])
	{
		val = get_env_value(env, "HOME");
		if (!val)
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (val);
	}
	if (are_strs_equal(args[1], "-"))
	{
		val = get_env_value(env, "OLDPWD");
		if (!val)
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		else
			*print_path = true;
		return (val);
	}
	return (args[1]);
}

// * Update OLDPWD and PWD environment variables
static int	update_pwd_vars(t_shell  *shell, char *oldpwd)
{
	char	cwd[1024];

	add_or_update_env(shell, "OLDPWD", oldpwd);
	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	add_or_update_env(shell, "PWD", cwd);
	return (0);
}