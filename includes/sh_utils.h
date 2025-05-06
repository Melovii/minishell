#ifndef SH_UTILS_H
# define SH_UTILS_H

# include "structs.h"

// * =======================================================>>>>> Cleanup utils

void	ft_free_tab(char **arr);
void	free_shell(t_shell *shell);
void	shut_program(t_shell *shell, bool need_msg, int exit_code);

// * =======================================================>>>>> String utils

void	skip_spaces(char *input, int *i);

bool	is_quote(char c);
bool	ft_isspace(char c);
bool	are_strs_equal(char *s1, char *s2);

char	*ultimate_join(char *s1, char *s2);
char	*ft_strjoin_path(char *dir, char *cmd);

// * =======================================================>>>>> Syntax utils

bool	check_syntax(t_token *tokens);
bool	does_included_quote(char *str);
bool	are_quotes_closed(t_token *tokens);

// * =======================================================>>>>> Path utils

void	path_error_msg(char *cmd, int exit_code, bool is_direct);

char	**get_paths_array(t_shell *shell);
char	*get_cmd_path(t_shell *shell, char *cmd, int *exit_code);

#endif
