#include "minishell.h"

static void	print_env_error(char *arg);

// * Function to print the environment variables
int	ft_env(t_shell *shell, char **args, bool is_export)
{
	t_env	*env;

	if (args[1])
	{
		print_env_error(args[1]);
		return (127);
	}
	env = shell->env;
	while (env)
	{
		if (is_export)
		{
			printf("declare -x %s", env->key);
			if (env->value)
				printf("=\"%s\"", env->value);
			printf("\n");
		}
		else
		{
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
	return (EX_OK);
}

static void	print_env_error(char *arg)
{
	ft_putstr_fd("minishell: env: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}


