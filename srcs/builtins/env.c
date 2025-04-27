#include "minishell.h"

// * Function to print the environment variables
int	ft_env(t_shell *shell, bool is_export)
{
	t_env	*env;

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

