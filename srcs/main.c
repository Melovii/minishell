#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

// * Function to clean up the shell (free_utils.c)
static void clean(t_shell *shell)
{
	if (!shell)
		return ;
	
	// TODO: Implement these function
	// free_env(shell);
	// free_tokens(shell->token);
	// free_cmd(shell->cmd);
}

// * Function to initialize the shell
static void	init_shell(t_shell *shell, char **envp)
{
	shell->exit_flag = 0;
	shell->env = NULL;
	shell->cmd = NULL;
	shell->token = NULL;
	init_env(shell, envp);
	// handle_signals();
}

// * Function to handle the shell loop
static void	shell_loop(t_shell *shell)
{
	char	*input;

	while (!shell->exit_flag)
	{
		input = readline(SHELL_NAME);
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		// shell->token = tokenizer(input);
		// shell->cmd = parse_input(input);
		// free(input);
		// if (shell->cmd)
			// execute_pipeline(shell->cmd);
		// free_tokens(shell->token);
		// free_cmd(shell->cmd);
	}
}

// * Main function
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (EXIT_FAILURE);

	init_shell(shell, envp);
	shell_loop(shell);
	// free_env();
	clean(shell);
	return (0);
}
