#include "minishell.h"

// static void	tokenise_input(t_shell *shell, char *input)
// {
// 	// TODO:
// 	// Control default input that without operators and quotes
// 	// Control ' and "  ---> by using sub-functions
// 	// Control operators ('|', '>>', '<<', '>', '<')
// 	// Split arguments and return tokenised linked list.
// 	// final process

// 	int	i;

// 	i = -1;
// 	while (input[++i])
// 	{
// 		if (input[i] == SPACE)
// 			continue ;
// 		else if (is_operator(input[i]))
// 			token_operator(shell, input, &i);
// 		else if (is_quote(input[i]))
// 		{
// 			cr_add_token(shell, &(shell->token_list), 
// 				token_quote(shell, input, &i, NULL), TK_WORD);
// 		}
// 		else
// 			cr_add_token(shell, &(shell->token_list), 
// 				token_default(shell, input, &i, NULL), TK_WORD);
// 	}
// }

// ? Example: ["ls", "-l", "|", "grep", "minishell", ">", "output.txt"]


void	process_input(t_shell *shell)
{
	while (is_interactive(shell))
		handle_interactive(shell);
	shell->is_interactive = C_FALSE;
	add_history(shell->history);
	shell->heredoc_list = NULL;  //! clear the  heredoc_list after the finish execution
	shell->heredoc_index = 0;	// ! same as above
	printf("%s\n", shell->input);
	// tokenise_input(shell, shell->input);
	// TODO: Create command linked list
	// TODO: Execute command
}
