#include "minishell.h"

static char		*get_oldpwd_or_error(void);
static int		do_cd(t_shell *shell, char **args);
static int		change_directory(t_shell *shell, char **args, char **target, bool *print_path);

// Entry point for 'cd' builtin
int	ft_cd(t_shell *shell, char **args)
{
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (EX_KO);
	}
	return (do_cd(shell, args));
}

// Main cd logic
static int	do_cd(t_shell *shell, char **args)
{
	char	*oldpwd;
	char	*target;
	bool	print_path;

	oldpwd = get_oldpwd_or_error();
	if (!oldpwd)
		return (EX_KO);
	if (change_directory(shell, args, &target, &print_path))
	{
		free(oldpwd);
		return (EX_KO);
	}
	if (print_path)
		ft_putendl_fd(target, STDOUT_FILENO);
	if (update_pwd_vars(shell, oldpwd))
	{
		ft_putendl_fd("minishell: cd: failed to update PWD", STDERR_FILENO);
		free(oldpwd);
		free(target);
		return (EX_KO);
	}
	free(oldpwd);
	free(target);
	return (EX_OK);
}

// Get current directory as OLDPWD (malloc'lı)
static char	*get_oldpwd_or_error(void)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		ft_putendl_fd("minishell: cd: getcwd error", STDERR_FILENO);
	return (oldpwd);
}

// Resolve and chdir to target
static int	change_directory(t_shell *shell, char **args, char **target, bool *print_path)
{
	*print_path = false;
	*target = get_cd_target(args, shell->env, print_path);
	if (!*target)
		return (EX_KO);
	if (chdir(*target) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(*target);
		free(*target);
		return (EX_KO);
	}
	return (EX_OK);
}


