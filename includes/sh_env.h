#ifndef SH_ENV_H
# define SH_ENV_H

# include "structs.h"

// * =======================================================>>>>> Init & Cleanup
void    init_env(t_shell *shell, char **envp);
void    free_env(t_env *node);
void    free_env_list(t_env *env);

// * =======================================================>>>>> Environment Variables
t_env   *create_env_node(t_shell *shell, char *env_var);
void    add_env_node(t_env **env_list, t_env *new_node);
t_env   *find_env_node(t_env *env, char *key);
void    set_env_key_value(t_shell *shell, t_env *node, char *env_var);
char    *get_env_value(t_env *env, char *key);

#endif
