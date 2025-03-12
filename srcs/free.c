#include "minishell.h"

static void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	clear_heredoc(shell);
	clear_token_list(shell);
	free(shell->input);
	free(shell->history);
	rl_clear_history();
	free(shell);
}

void	shut_program_err(t_shell *shell)
{
	free_shell(shell);
	exit(EXIT_FAILURE);
}

void	shut_program_err(t_shell *shell)
{
	free_shell(shell);
	exit(EXIT_SUCCESS);
}

void	make_ready_for_next_prompt(t_shell *shell)
{
	if (!shell)
		return ;
	add_history(shell->history);
	shell->heredoc_index = 0;
	shell->is_interactive = C_FALSE;
	clear_heredoc(shell);
	clear_token_list(shell);
	free(shell->history);
	free(shell->input);
	shell->history = NULL;
	shell->input = NULL;
}