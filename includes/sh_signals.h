#ifndef SH_SIGNALS_H
# define SH_SIGNALS_H

# include <signal.h>

# include "structs.h"

// * =======================================================>>>>> Signal Handling
int		setup_termios(t_shell *shell, t_termios_action action);
void	handle_signals(t_status status);
void	handle_sigint_output(void);

#endif
