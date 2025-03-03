#include "minishell.h"

void	shell_loop(void)
{
	char	*input;
	
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)	// * Handles Ctrl + D
		{
			printf("exit\n");
			break ;
		}
		
		printf("%s\n", input); // ? test
		add_history(input); // ? do we need to use rl_clear_histroy for leaks ?
		// process_input(input); // TODO: Implement this function
		free(input); // ? is this necessary
	}
	// TODO:
	// // Display a prompt (minishell$ ).
	// Read user input (Parse & Tokenise).
	// Process and execute the command.
	// // Add the command that is run to history.
	// // Repeat until the user exits.
}

int	main(int argc, char **argv, char **envp)
{
	setup_signals(); // TODO: Implement this function
	shell_loop();
	return (0);
}
