#include "minishell.h"

static bool	is_numeric(const char *str);
static void	numeric_exit(t_shell *shell, char **args, int exit_code);
static void custom_exit_msg(char *flag);

// * Handles the exit command by checking arguments and shutting down the program
int	ft_exit(t_shell *shell, char **args)
{
	int	exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!args[1])
	{
		ft_free_tab(args);
        shut_program(shell, false, shell->exit_flag);
	}
	if (!is_numeric(args[1]))
	{
		custom_exit_msg(args[1]);
		ft_free_tab(args);
        shut_program(shell, false, 2);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		shell->exit_flag = EX_KO;
		return (EX_KO);
	}
	exit_code = ft_atoi(args[1]) % 256;
	numeric_exit(shell, args, exit_code);
	return (0);
}

// Handles numeric exit: adjusts negative exit code, frees args, and exits shell
static void	numeric_exit(t_shell *shell, char **args, int exit_code)
{
	if (exit_code < 0)
		exit_code += 256;
	ft_free_tab(args);
    shut_program(shell, false, exit_code);
}

// * Prints a custom error message when the exit argument is invalid
static void custom_exit_msg(char *flag)
{
    if (!flag)
        return;
    ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
    ft_putstr_fd(flag, STDERR_FILENO);
    ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

// * Determines if a string represents a valid numeric value (integer)
static bool	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}
