#include "minishell.h"

// TODO: Change strcmp to are_equal_aksfimasfm

int	is_builtin(char *cmd)
{
	if (!strcmp(cmd, "cd"))
		return (1);
	if (!strcmp(cmd, "echo"))
		return (1);
	if (!strcmp(cmd, "pwd"))
		return (1);
	if (!strcmp(cmd, "export"))
		return (1);
	if (!strcmp(cmd, "unset"))
		return (1);
	if (!strcmp(cmd, "env"))
		return (1);
	if (!strcmp(cmd, "exit"))
		return (1);
	return (0);
}

// TODO: Implement the built-in functions in srcs/builtins

int	exec_builtin(t_shell *shell, char **args)
{
	if (strcmp(args[0], "cd") == 0)
		return ft_cd(args);

	if (strcmp(args[0], "echo") == 0)
		return ft_echo(args);

	if (strcmp(args[0], "pwd") == 0)
		return ft_pwd();

	// if (strcmp(args[0], "export") == 0)
	// 	return ft_export(shell, args);

	// if (strcmp(args[0], "unset") == 0)
	// 	return ft_unset(shell, args);

	if (strcmp(args[0], "env") == 0)
		return ft_env(shell);

	if (strcmp(args[0], "exit") == 0)
		return ft_exit(args);

	// If not a built-in, return -1
	return (-1);
}
