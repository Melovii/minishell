#include "minishell.h"

// * Function to exit the shell
// TODO: Check if I even need to handle string exit codes
// ! IMPORRTANT:
// TODO: MAKE SURE SHELL EXITS CLEANLY, FREEING ALL ALLOCATED MEMORY
int	ft_exit(char **args)
{
	printf("exit\n");

	if (!args[1]) // No arguments: exit with success
		exit(0);
	if (!is_numeric(args[1])) // Check if the argument is a valid number
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	if (args[2]) // More than one argument
	{
		printf("minishell: exit: too many arguments\n");
		return (1); // Do not exit
	}
	exit(ft_atoi(args[1])); // Convert string to int and exit
}
