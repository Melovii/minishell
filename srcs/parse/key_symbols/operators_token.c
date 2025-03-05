#include "minishell.h"

static void	handle_input_rdrct(t_shell *shell, char *input, int *i);
static void	handle_output_rdrct(t_shell *shell, char *input, int *i);
static void	handle_pipe(t_shell *shell, char *input, int *i);

// * purpose: tokenizing "| << < > >>" operators
// * parameters:	(shell)-> main struct, (input)-> str from client
// *				(i/index)-> current input index
void	token_operator(t_shell *shell, char *input, int *i)
{
	if (input[*i] == PIPE)
		handle_pipe(shell, input, i);
	else if (input[*i] == INPUT_RDRCT)
		handle_input_rdrct(shell, input, i);
	else
		handle_output_rdrct(shell, input, i);
}

static void	handle_pipe(t_shell *shell, char *input, int *i)
{
	if (is_operator(input[*i + 1]))
		shut_program_err(shell);
	else
		cr_add_token(shell, &(shell->token_list), "|", TK_PIPE);
	(*i) += 1;
}

static void	handle_input_rdrct(t_shell *shell, char *input, int *i)
{
	if (input[(*i) + 1] == INPUT_RDRCT)
	{
		if (is_operator(input[(*i) + 2]))
		{
			shut_program_err(shell) ; // !  error handling should be :(
		}
		else
			cr_add_token(shell, &(shell->token_list), "<<", TK_HEREDOC);
		(*i) += 1;
	}
	else if (input[(*i) + 1] == OUTPUT_RDRCT | input[(*i) + 1] == PIPE)
		shut_program_err(shell);
	else
		cr_add_token(shell, &(shell->token_list), "<", TK_RED_IN);
}

static void	handle_output_rdrct(t_shell *shell, char *input, int *i)
{
	if (input[(*i) + 1] == OUTPUT_RDRCT)
	{
		if (is_operator(input[(*i) + 2]))
			shut_program_err(shell) ; // !  error handling should be :(
		else
			cr_add_token(shell, &(shell->token_list), ">>", TK_APPEND);
		(*i) += 1;
	}
	else if (input[(*i) + 1] == INPUT_RDRCT | input[(*i) + 1] == PIPE)
		shut_program_err(shell);
	else
		cr_add_token(shell, &(shell->token_list), ">", TK_RED_OUT);
}
