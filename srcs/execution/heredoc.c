#include "minishell.h"

// ? assume that you have already parsed heredoc content
// ? this will store it in the cmd->heredoc_delim and set an "is_heredoc" flag

// * FLOW:
// parse tokens -> set heredoc_delim and has_heredoc
// before execution, call init_heredoc() if needed
// during execution, call redirect_heredoc() before exec()
// clean up file descriptors after command runs

// 1. parse_heredoc() will set the delim and has_heredoc flag
// 2. init_heredoc() will create a pipe and fork (by calling fork_heredoc())
// 3. handle_heredoc_input() will read input until EOF or delim
// 4. write valid lines to the pipe (until EOF or delim)
// 5. close the pipe in the parent process
// 6. redirect_heredoc() will redirect the command's stdin to the pipe
// 7. clean up the file descriptors after command runs
// 8. free the heredoc delim and has_heredoc flag in the cmd struct
// 9. handle Ctrl+C and Ctrl+D signals in the child process (set_heredoc_signals() and sigint_heredoc_handler())
// 10. handle EOF and delim in the parent process

// Parser 	->  sets `heredoc_delim`, `has_heredoc`

// Init   	->  call `init_heredoc()` before exec
//         	->  creates pipe
//         	->  forks child to collect input via `readline`
//         	->  stores read-end of pipe in `cmd->heredoc_fd`

// Exec   	->  before execve, call `redirect_heredoc()`
//         	->  dup2(heredoc_fd, STDIN_FILENO)

// Signals	->  child process uses custom SIGINT handler
//         	->  Ctrl+C aborts heredoc input cleanly


// // 1. During parsing:
// if (token_is("<<"))
// 	parse_heredoc(cmd, next_token());

// // 2. Before execution:
// if (cmd->has_heredoc)
// 	init_heredoc(cmd);

// // 3. Right before exec:
// redirect_heredoc(cmd);
// execve(cmd->args[0], cmd->args, env);

// // 4. After execution:
// close_fds(cmd);

// ok let's start working:
// parse_heredoc function
int	parse_heredoc(t_cmd *cmd, t_token *token)
{
	if (token->type == HEREDOC)
	{
		cmd->heredoc_delim = ft_strdup(token->value);
		if (!cmd->heredoc_delim)
			return (1);
	}
	cmd->has_heredoc = true;
	return (0);
}


// ! FORK for heredoc to handle signals
int	fork_heredoc(const char *delim, int write_fd)
{
	// ? check the COPILOT code
	// int		status;

	// pid_t pid = fork();
	// if (pid == 0)
	// {
		// set_heredoc_signals();
		// handle_heredoc_input(...);
	// 	exit(0);
	// }
	// waitpid(pid, &status, 0);
}

// called before command exection
int	init_heredoc(t_cmd *cmd)
{
	// if (cmd->heredoc_delim) is set {
	// create a pipe
	// read input until EOF/delim
	// writes to pipe (which will write to the cmd->in_fd or somewhere later on)
	// sets cmd->heredoc_fd (for later redirection)
	return (0); // error
}

int	handle_heredoc_input(const char *delim, int write_fd)
{
	// loop with readline
	readline(HEREDOC_PROMPT);
	// compare each line to delim
	// write valid lines to write_fd
	// ! DO NOT FORGET TO: handle Ctrl+C
	// exit on EOF or delim
}
