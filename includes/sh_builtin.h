#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

# include "structs.h"

// * =======================================================>>>>> Built-in Commands

bool	is_builtin(t_token *token_lst);
int		execute_builtin(t_shell *shell, t_cmd *cmd);

int		update_pwd_vars(t_shell *shell, char *oldpwd);
char	*get_cd_target(char **args, t_env *env, bool *print_path);

int		ft_echo(char **args);
int		ft_pwd(t_shell *shell);
int		ft_cd(t_shell *shell, char **args);
int		ft_env(t_shell *shell, char **args);
int		ft_exit(t_shell *shell, char **args);
int		ft_unset(t_shell *shell, char **args);
int		ft_export(t_shell *shell, char **args);

// * =======================================================>>>>> Helpers

void	print_export(t_shell *shell);
void	add_or_update_env(t_shell *shell, char *key, char *value);

bool	is_valid_identifier(char *key);

t_env	*parse_export_argument(t_shell *shell, char *arg);

#endif
