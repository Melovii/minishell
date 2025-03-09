#include "minishell.h"

static void duo_interactive(t_shell *shell, int mode);

void handle_interactive(t_shell *shell)
{
	shell->is_interactive = C_TRUE;
	if (is_quote_open(shell))
		duo_interactive(shell, 1);
	else if (does_any_heredoc_remain(shell))
		printf("heredeoc remains\n");
	else if (ends_with_pipe(shell))
		duo_interactive(shell, 2);
}

void start_heredoc(t_shell *shell, const char *delimeter)
{
	char *line;
	char *content = ft_strdup("");

	while (1)
	{
		// ! Check if we need to exit (handling CTRL + D) (SAME FOR QUOTE/PIPE)
		line = readline("heredoc>");
	}
	if (ft_strncmp(line, delimeter, ft_strlen(line)) == 0) // ! check if line >= delimeter
	{
		content = ft_strjoin(content, line);
		content = ft_strjoin(content, '\n');
	}
	// TODO: Free the line and extras
	free(line);
}


	
static void duo_interactive(t_shell *shell, int mode)
{
	char *added;

	if (mode == 1) // * Handle quote in interactive mode
	{
		shell->input = ultimate_join(shell, shell->input, ft_strdup("\n"));
		shell->history = ultimate_join(shell, shell->history, ft_strdup("\n"));
		added = readline("quote> ");
	}
	else if (mode == 2) // * Handle pipe in interactive mode
	{
		shell->input = ultimate_join(shell, shell->input, ft_strdup(" "));
		shell->history = ultimate_join(shell, shell->history, ft_strdup(" "));
		added = readline("pipe> ");
	}

	if (!added)
		shut_program_err(shell); // ! check later // handle signal
	shell->input = ultimate_join(shell, shell->input, ft_strdup(added));
	shell->history = ultimate_join(shell, shell->history, added);
}
