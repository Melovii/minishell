#include "minishell.h"

static void duo_interactive(t_shell *shell, int mode);
static void start_heredoc(t_shell *shell);

void handle_interactive(t_shell *shell)
{
	shell->is_interactive = C_TRUE;
	if (is_quote_open(shell))
		duo_interactive(shell, 1);
	else if (does_any_heredoc_remain(shell))
		start_heredoc(shell);
	else if (ends_with_pipe(shell))
		duo_interactive(shell, 2);
}

static void start_heredoc(t_shell *shell)
{
	heredoc_interactive(shell, shell->input);
	fill_heredocs(shell);
}


static void duo_interactive(t_shell *shell, int mode)
{
	char *added;

	if (mode == 1) // * Handle quote in interactive mode
	{
		shell->input = ultimate_join(shell, shell->input, ft_strdup("\n"));
		shell->history = ultimate_join(shell, shell->history, ft_strdup("\n"));
		added = readline("quote> ");
		if (!added)
			shut_program_err(shell);
	}
	else if (mode == 2) // * Handle pipe in interactive mode
	{
		shell->input = ultimate_join(shell, shell->input, ft_strdup(" "));
		shell->history = ultimate_join(shell, shell->history, ft_strdup(" "));
		added = readline("pipe> ");
		if (!added)
			shut_program_err(shell);
	}

	if (!added)
		shut_program_err(shell);
	shell->input = ultimate_join(shell, shell->input, ft_strdup(added));
	shell->history = ultimate_join(shell, shell->history, added);
}
