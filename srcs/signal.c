#include "minishell.h"

// * Handling Signals (Ctrl+C, Ctrl+D, Ctrl+\)
// Handle user interrupts and termination signals gracefully
// Ensure Minishell behaves correctly when receiving signals like SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)

void signal_handler(int signum)
{
	// TODO:
	// Handle SIGINT (Ctrl+C) by printing a new prompt line instead of terminating
	// Handle SIGQUIT (Ctrl+\) by printing "Quit" but preventing core dumps
	// Optionally, handle SIGTERM or SIGSTOP if needed
}

void setup_signals(void)
{
	// TODO:
	// Set up signal handling for SIGINT and SIGQUIT
	// Use signal() or sigaction() for better control
}
