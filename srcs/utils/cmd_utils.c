#include "minishell.h"

char **refill_cmd_args(char **old, int len, char *value)
{
	char	**new;
	int	i;

	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[len] = ft_strdup(value);
	if (!(new[len]))
		return (NULL);  // ! check for error handling
	new[len + 1] = NULL;
	free(old);
	return (new);
}

// * Purpose: To initialize cmd structure with initial values
void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->in_fd = 0; // ? IS THIS CORRECT?
	cmd->out_fd = 1; // ? IS THIS CORRECT?
	cmd->append = false;
	cmd->next = NULL;
}
