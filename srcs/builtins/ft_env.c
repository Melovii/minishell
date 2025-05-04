#include "minishell.h"

static void	print_env_error(char *arg);

// * Function to print the environment variables
int	ft_env(t_shell *shell, char **args)
{
	t_env	*env;

	if (args[1])
	{
		print_env_error(args[1]);
		return (CMD_NOT_FOUND);
	}
	env = shell->env;
	while (env)
	{
		if (env->value)
		{
			printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
	return (EX_OK);
}

// * Prints an error message when an invalid argument is provided to the env command
static void	print_env_error(char *arg)
{
	ft_putstr_fd("minishell: env: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}


