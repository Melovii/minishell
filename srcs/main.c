#include "minishell.h"
#include "../libft/libft.h"

static void init_shell(t_shell *shell, char **envp);
static void make_ready_for_next_prompt(t_shell *shell);
static void shell_loop(t_shell *shell);

// * Main function
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

    // TODO: Add signal handling

	(void)argv;
	if (argc != 1) // TODO: Add invalid number of arguments error code (2)
		shut_program(NULL, "Invalid number of arguments", INV_ARGC);
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
	{
		perror("minishell");
		return (EX_KO);
	}
	init_shell(shell, envp);
	shell_loop(shell);
	free_shell(shell);
	return (0);
}

static void shell_loop(t_shell *shell)
{
	char *prompt;

	while (1)
	{
        make_ready_for_next_prompt(shell); // ? Is double checking needed? ->> Probably
		prompt = readline(PROMPT);
		if (!prompt)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (prompt[0] != '\0')
			add_history(prompt);
        shell->input = prompt;
        (shell->number_of_prompts)++;
		tokenizer(shell, prompt);
        if (!(check_syntax(shell->token) && are_quotes_closed(shell->token)))
            continue;
        parser(shell);
        shell->num_pipes = count_pipes(shell->cmd);
        print_cmd_list(shell->cmd); // ! Will be removed later
        execution(shell);
        make_ready_for_next_prompt(shell);
	}
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
    // TODO: Update later
}

static void init_shell(t_shell *shell, char **envp) // ? Check if this is needed
{
	shell->input = NULL;
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
