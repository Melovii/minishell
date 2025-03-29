#include "minishell.h"

// * Function to print the environment variables
int	ft_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	if (!env || !env->key || !env->value) // TODO: Check if this is correct/necessary
		return (EX_KO);
	while (env)
	{
		//?	should I printf or write?
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (EX_OK);
}
