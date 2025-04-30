#include "minishell.h"
#include "../libft/libft.h"

static void init_shell(t_shell *shell, char **envp);
static void make_ready_for_next_prompt(t_shell *shell);
static void general_process(t_shell *shell, char *prompt);
static void shell_loop(t_shell *shell);

// * Main function
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

    // TODO: Add signal handling

	(void)argv;
	if (argc != 1) // TODO: Add invalid number of arguments error code (2)
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
	init_shell(shell, envp);
	setup_termios(shell, SAVE);
	shell_loop(shell);
	setup_termios(shell, LOAD);
	free_shell(shell);
	return (0);
}

static void shell_loop(t_shell *shell)
{
	char *prompt;

	while (1)
	{
		handle_signals(STANDBY);
        make_ready_for_next_prompt(shell);
		prompt = readline(PROMPT);
		if (!prompt)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		handle_signals(NEUTRAL);
		if (prompt[0] == '\0')
		{
			continue ;
		}
		general_process(shell, prompt);
        make_ready_for_next_prompt(shell);
	}
}

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
	shell->cur_exit_flag = process_heredocs(shell); // ! Check (exit code + signal handling) out
    if (shell->cur_exit_flag != EX_OK)
        return ;
	expand_and_unquote_cmd_list(shell);
    execution(shell);
}

static void make_ready_for_next_prompt(t_shell *shell)
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
    // TODO: Update later
}

static void init_shell(t_shell *shell, char **envp) // ? Check if this is needed
{
	shell->input = NULL;
	shell->cur_exit_flag = 0;
	shell->exit_flag = 0;
    shell->number_of_prompts = 0;
	shell->num_pipes = 0;
	shell->og_env = envp;
	init_env(shell, envp);
    shell->num_pipes_fd = NULL;
	shell->cmd = NULL;
	shell->token = NULL;
	// g_signal = 0; // ?  Is this supposed to be here?
}
