#include "minishell.h"

static void prepare_for_next_prompt(t_shell *shell);
static void general_process(t_shell *shell, char *prompt);
static void shell_loop(t_shell *shell);

// * Initializes and runs the shell program
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("Error: Invalid number of arguments", STDERR_FILENO);
		return (INV_ARGC);
	}
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
	{
		perror("minishell");
		return (EX_KO);
	}
	init_env(shell, envp);
	setup_termios(shell, SAVE);
	shell_loop(shell);
	setup_termios(shell, LOAD);
	free_shell(shell);
	return (0);
}

// * Main loop for reading and processing commands
static void shell_loop(t_shell *shell)
{
	char *prompt;

	while (1)
	{
		handle_signals(STANDBY);
        prepare_for_next_prompt(shell);
		prompt = readline(PROMPT);
		handle_signals(NEUTRAL);
		if (!prompt)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (prompt[0] == '\0')
		{
			continue ;
		}
		general_process(shell, prompt);
        prepare_for_next_prompt(shell);
	}
}

// * Process the input: tokenize, parse, and execute
static void general_process(t_shell *shell, char *prompt)
{
	add_history(prompt);
	shell->input = prompt;
    (shell->number_of_prompts)++;
	tokenizer(shell, prompt);
    if (!(check_syntax(shell->token) && are_quotes_closed(shell->token)))
        return ;
    parser(shell);
	shell->num_pipes = count_pipes(shell->cmd);
	shell->num_pipes_fd = setup_pipes(shell, shell->num_pipes);
	shell->cur_exit_flag = process_heredocs(shell);
    if (shell->cur_exit_flag != EX_OK)
	{
        return ;
	}
	expand_and_unquote_cmd_list(shell);
    execution(shell);
}

// * Clean up resources and prepare for next prompt
static void prepare_for_next_prompt(t_shell *shell)
{
    if (shell->input)
        free(shell->input);
    shell->input = NULL;
    free_tokens(shell->token);
    shell->token = NULL;
    free_cmd_list(shell->cmd);
    shell->cmd = NULL;
    free_pipe_fd(shell->num_pipes_fd, shell->num_pipes);
    shell->num_pipes_fd = NULL;
    shell->num_pipes = 0;
	shell->exit_flag = shell->cur_exit_flag;
}
