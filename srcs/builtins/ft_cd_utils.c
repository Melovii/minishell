#include "minishell.h"

static bool	is_tilde_path(char *s);
static char	*expand_tilde(char *arg);
static char	*get_oldpwd_path(t_env *env, bool *print_path);

// * Update PWD and OLDPWD using malloc'lı getcwd()
int	update_pwd_vars(t_shell *shell, char *oldpwd)
{
	char	*cwd;

	add_or_update_env(shell, "OLDPWD", oldpwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EX_KO);
	add_or_update_env(shell, "PWD", cwd);
	free(cwd);
	return (EX_OK);
}

// * Determine target path for 'cd'
char	*get_cd_target(char **args, t_env *env, bool *print_path)
{
	char	*val;
	char	*result;

	if (!args[1])
	{
		val = get_env_value(env, "HOME");
		if (!val)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (NULL);
		}
		result = ft_strdup(val);
		return (result);
	}
	if (are_strs_equal(args[1], "-"))
	{
        return (get_oldpwd_path(env, print_path));
	}
	if (is_tilde_path(args[1]))
    {
		return (expand_tilde(args[1]));
    }
	return (ft_strdup(args[1]));
}

// * Check if arg is '~' or '~/...'
static bool	is_tilde_path(char *s)
{
	return (s && s[0] == '~' && (s[1] == '\0' || s[1] == '/'));
}

// * Convert '~' to HOME, no matter if $HOME exist or not
static char	*expand_tilde(char *arg)
{
	char	*home;
	char	*expanded;

	home = getenv("HOME");
	if (!home)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (NULL);
	}
	if (arg[1] == '\0')
		return (ft_strdup(home));
	expanded = ft_strjoin(home, arg + 1);
	if (!expanded)
	{
		ft_putendl_fd("minishell: cd: memory allocation error", STDERR_FILENO);
		return (NULL);
	}
	return (expanded);
}

// * Retrieve OLDPWD path for 'cd -' and enable printing if available
static char	*get_oldpwd_path(t_env *env, bool *print_path)
{
	char	*val;
	char	*result;

	val = get_env_value(env, "OLDPWD");
	if (!val)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		return (NULL);
	}
	*print_path = true;
	result = ft_strdup(val);
	return (result);
}
