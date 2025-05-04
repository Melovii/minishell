#include "minishell.h"
#include "../libft/libft.h"

void	handle_sigint_output(void)
{
	if (isatty(STDOUT_FILENO))
		ft_putchar_fd('\n', STDOUT_FILENO);
}

// * Function to handle SIGINT signal (standby mode)
static void	handle_interrupt(int sig)
{
	(void)sig;
	handle_sigint_output();
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// * Function to handle SIGINT signal (heredoc mode)
static void	signal_heredoc(int sig)
{
	(void)sig;
	handle_sigint_output();
	exit(130);
}

// * Function to handle SIGINT signal (command mode)
static void	signal_cmd(int sig)
{
	(void)sig;
	exit(130);
}

// * Default signals function
void	handle_signals(t_status status)
{
	signal(SIGQUIT, SIG_IGN);
	if (status == STANDBY)
	{
		signal(SIGINT, handle_interrupt);
	}
	else if (status == EXEC_HRDC)
	{
		signal(SIGINT, signal_heredoc);
	}
	else if (status == EXEC_CMD)
	{
		signal(SIGINT, signal_cmd);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
	}
}
