#include "minishell.h"

// * Function to change directory
int	ft_cd(char **args)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Current directory: %s\n", cwd);
	
	if (chdir(args[1]) == -1)
	{
		perror("chdir");
		return (-1);
	}

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Directory after chdir: %s\n", cwd);
	
	return (0);
}
