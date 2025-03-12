#include "minishell.h"

void	shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input) // * Handles Ctrl + D
		{
			printf("exit\n");
			shut_program_err(shell);
		}
		shell->input = input;
		shell->history = ft_strdup(shell->input);
		process_input(shell);
	}
	// TODO:
	// // Display a prompt (minishell$ ).
	// // Read user input (Parse & Tokenise).
	// Process and execute the command.
	// // Add the command that is run to history.
	// // Repeat until the user exits.
}

//* purpose: initialization of main structure (t_shell)

t_shell	*init_shell(void)
{
	t_shell	*new;

	new = ft_calloc(1, sizeof(t_shell));
	if (!new)
		return (NULL);
	new->is_interactive = C_FALSE;
	return (new);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = init_shell();
	if (!shell)
		return (ALLOC_ERR); // ? special message for any error maybe?
	setup_signals();
	shell_loop(shell);
	return (0);
}
