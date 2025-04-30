#include "minishell.h"

// TODO: Check if I should return something else instead of EX_OK etc.
// * Function to setup termios flags
int	setup_termios(t_shell *shell, t_termios_action action)
{
	t_termios	termios;
	
	if (action == SAVE)
	{
		if (tcgetattr(STDIN_FILENO, &termios))
			return (EX_KO);
		shell->termios = termios; 
		termios.c_lflag |= ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios))
			return (EX_KO);
	}
	else if (action == LOAD
		&& tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->termios))
	{
		return (EX_KO);
	}
	return (EX_OK);
}
