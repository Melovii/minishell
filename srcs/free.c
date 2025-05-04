#include "minishell.h"

// * Shuts down the program, optionally prints error message and exits
void	shut_program(t_shell *shell, bool need_msg, int exit_code)
{
    if (need_msg)
    {
        perror("minishell");
    }
    if (!shell)
    {
        clear_history();
        return ;
    }
    free_shell(shell);
    exit(exit_code);
}

// * Frees all allocated memory for the shell
void    free_shell(t_shell *shell)
{
    if (!shell)
        return ;
    clear_history();
    if (shell->input)
        free(shell->input);
    free_tokens(shell->token);
    free_cmd_list(shell->cmd);
    free_env_list(shell->env);
    free_pipe_fd(shell->num_pipes_fd, shell->num_pipes);
    free(shell);
}

// * Frees each string in a 2D array (char **)
void	ft_free_tab(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
