#include "minishell.h"

static void free_shell(t_shell *shell)
{
    if (shell)
    {
        free(shell);
    }
}

void    shut_program_err(t_shell *shell)
{
    free_shell(shell);
    exit(EXIT_FAILURE);
}
