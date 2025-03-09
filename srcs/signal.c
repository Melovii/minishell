// TODO: Understand why I can't use these in header file
# define _XOPEN_SOURCE 700
// # define _POSIX_C_SOURCE 200809L

#include "minishell.h"
// * Handling Signals (Ctrl+C, Ctrl+D, Ctrl+\)
// Handle user interrupts and termination signals gracefully
// Ensure Minishell behaves correctly when receiving signals like SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)

// TODO: handle interactive mode signals and memory leaks

void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		// Handle SIGINT (Ctrl+C) by printing a new prompt line instead of terminating
		printf("\n");
		rl_on_new_line();	// * reset readline buffer
		rl_replace_line("", 0);	// * clear the current input line
		rl_redisplay();	// * refresh the prompt line
	}
	else if (signum == SIGQUIT)
	{
		// Handle SIGQUIT (Ctrl+\) by printing "Quit" but preventing core dumps
		printf("Quit\n");
	}
	// * OPTIONAL: handle SIGTERM or SIGSTOP if needed
}

// * Set up signal handling for SIGINT and SIGQUIT
void setup_signals(void)
{
	struct sigaction	sa;

	// Handle SIGINT (Ctrl+C)
	// ft_bzero(&sa, sizeof(sa)); // * Check if necessary
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction SIGINT error");
		exit(1);
	}

	// Ignore SIGQUIT (Ctrl+\)
	sa.sa_handler = SIG_IGN; // Ignore the signal
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction SIGQUIT error");
		exit(1);
	}
}
