#include "minishell.h"

static void handle_input_rdrct(t_shell	*shell, char *input, int *i);


// * purpose: tokenizing "| << < > >>" operators
// * parameters:	(shell)-> main struct, (input)-> str from client
// *				(i/index)-> current input index
void	token_operator(t_shell	*shell, char *input, int *i)
{
	if (input[*i] == PIPE)
		cr_add_token(shell, &(shell->token_list), "|", TK_PIPE);
	else if (input[*i] == INPUT_RDRCT)
		handle_input_rdrct(shell, input, i);
	else
		handle_output_rdrct(shell, input, i);
}

static void handle_input_rdrct(t_shell	*shell, char *input, int *i)
{
	if (input[(*i) + 1] == INPUT_RDRCT)
	{
		if (input[(*i) + 2] == INPUT_RDRCT)
			return ; // !  error handling should be :(
		else
			cr_add_token(shell, &(shell->token_list), "<<", TK_HEREDOC);
		(*i) += 1;
	}
	else
		cr_add_token(shell, &(shell->token_list), "<", TK_RED_IN);
}

static void	handle_output_rdrct(t_shell *shell, char *input, int *i)
{
	if (input[(*i) + 1] == OUTPUT_RDRCT)
	{
		if (input[(*i) + 2] == OUTPUT_RDRCT)
			return ; // !  error handling should be :(
		else
			cr_add_token(shell, &(shell->token_list), ">>", TK_APPEND);
		(*i) += 1;
	}
	else
		cr_add_token(shell, &(shell->token_list), ">", TK_RED_OUT);
}
