#ifndef SH_EXEC_H
# define SH_EXEC_H

# include "structs.h"

// * =======================================================>>>>> Execution

void	execution(t_shell *shell);
void	print_dir_error(char *cmd);
void	print_open_error(char *filename);
void	free_pipe_fd(int **pipe_fd, int num);
void	eof_msg(t_shell *shell, char *delimiter);
void	close_unused_pipes(t_shell *shell, int current);
void	child_process(t_shell *shell, t_cmd *cmd, int i);

char	**modify_args(t_cmd *cmd);

bool	cmd_is_dir(char *cmd);

int		count_pipes(t_cmd *cmd);
int		process_heredocs(t_shell *shell);
int		**setup_pipes(t_shell *shell, int num_pipes);

// * =======================================================>>>>> Redirection

void	close_all_pipes(t_shell *shell);
void	close_redirections(t_cmd *cmd_list);
void	parse_redirection(t_shell *shell, t_cmd *cmd);

bool	has_input_redirection_via_list(t_cmd *cmd);
bool	has_output_redirection_via_list(t_cmd *cmd);
bool	file_path_name_expansion(t_shell *shell, t_dir *dir);
bool	setup_redirections_with_pipe(t_shell *shell, t_cmd *cmd, int i);

#endif
