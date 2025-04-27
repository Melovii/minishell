#include "minishell.h"
#include "../libft/libft.h"

// * Function to change directory
int	ft_cd(char **args, t_env *env)
{
	char	*target;

	if (!args[1])
	{
		target = get_env_value(env, "HOME");
		if (!target)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (1);
		}
	}
	else
		target = args[1];

	if (chdir(target) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(target);
		return (1);
	}
	return (0);
}
