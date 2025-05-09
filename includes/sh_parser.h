#ifndef SH_PARSER_H
# define SH_PARSER_H

# include "structs.h"

// * =======================================================>>>>> Commands

int		get_len_cmd_args(t_cmd *cmd);

void	parser(t_shell *shell);
void	free_cmd_list(t_cmd *head);

t_cmd	*new_cmd_node(t_shell *shell);

// * =======================================================>>>>> Redirection

void	add_redir_node(t_dir **redir_list, t_dir *new_node);
t_dir	*create_redir_node(t_shell *shell, t_redir_type type, char *filename);

#endif
