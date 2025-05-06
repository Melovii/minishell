#include "minishell.h"

void null_path_name_msg(char *before_expansion);

// * Expands the file path name for redirections and handles potential errors
bool    file_path_name_expansion(t_shell *shell, t_dir *dir)
{
    char    *before_expansion;

    if (dir->type == DIR_HEREDOC)
        return (true);
    before_expansion = dir->filename;
    dir->filename = expand_vars(shell, dir->filename);
    if (dir->filename == NULL)
    {
        null_path_name_msg(before_expansion);
        return (false);
    }
    dir->filename = remove_quotes_update_str(shell, dir->filename);
    return (true);
}

// * Prints an error message for ambiguous redirects
void null_path_name_msg(char *before_expansion)
{
    ft_putstr_fd("bash: ", STDERR_FILENO);
    ft_putstr_fd(before_expansion, STDERR_FILENO);
    ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
}
