#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

/**
 **	Purpose: Clear and reset shell data for next command
 * 	@shell: Pointer to the shell structure
 */
static void make_ready_for_next_prompt(t_shell *shell)
{
	if (!shell)
		return ;
	
	// TODO: Implement these function
	free_tokens(shell->token);
	free_cmd(shell->cmd);
	free(shell->input);
	shell->cmd = NULL;
	shell->token = NULL;
	shell->input = NULL;
}

/**
 ** Purpose: Initialize shell structure and environment
 * 	@shell: Pointer to the shell structure to be initialized
 * 	@envp: Array of environment variables passed to the program
 */
static void	init_shell(t_shell *shell, char **envp)
{
	shell->exit_flag = 0;
	shell->env = NULL;
	shell->cmd = NULL;
	shell->token = NULL;
	shell->og_env = envp;
	init_env(shell, envp);
	// handle_signals();
}

/** 
**	shell_loop - Main loop to handle user input and execute commands
* 	@shell: Pointer to the shell structure
*/
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
		shell->input = input;
		if (is_quote_open(input))
		{
			free(input);
			ft_putendl_fd("minishell: syntax error: unclosed quotes", 2);
			continue ;
		}
		shell->token = tokenizer(input);
		if (!shell->token)   // * In order to prevent SEGFAULT
		{
			free(input);
			continue ;
		}
		expander(shell);  // TODO:  Implement expander function
		print_tokens(shell->token);	// ! DEBUGGING ONLY
		shell->cmd = parse_input(shell);
		// print_cmd_list(shell->cmd);	// ! DEBUGGING ONLY
		if (shell->cmd)
			exec_cmd(shell, shell->cmd);
		make_ready_for_next_prompt(shell);
	}
}

// * Main function
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argv;
	if (argc != 1) // TODO: Add invalid number of arguments error code (2)
		handle_error("Invalid number of arguments", 2);
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (EXIT_FAILURE);
	init_shell(shell, envp);
	shell_loop(shell);
	free_shell(shell);
	return (0);
}
