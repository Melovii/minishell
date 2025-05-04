#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

# include "structs.h"

// * =======================================================>>>>> Built-in Commands

bool    is_builtin(t_token *token_lst);
int     execute_builtin(t_shell *shell, t_cmd *cmd);

int     ft_echo(char **args);
int     ft_pwd(t_shell *shell);
int     ft_cd(t_shell *shell, char **args);
int     ft_env(t_shell *shell, char **args);
int     ft_exit(t_shell *shell, char **args);
int     ft_unset(t_shell *shell, char **args);
int     ft_export(t_shell *shell, char **args);



// * =======================================================>>>>> Helpers

void    print_export(t_shell *shell);
void    add_or_update_env(t_shell *shell, char *key, char *value);
t_env   *parse_export_argument(t_shell *shell, char *arg);

#endif
