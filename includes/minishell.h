#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <stdbool.h>
# include <termios.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "structs.h"

# define EX_OK EXIT_SUCCESS
# define EX_KO EXIT_FAILURE

# define INV_ARGC 2

# define HEREDOC_PIPE_ERROR 1
# define HEREDOC_FORK_ERROR 2
# define HEREDOC_EXIT_INTERRUPTED 130

# define PROMPT "minishell> "
# define HEREDOC_PROMPT "heredoc> "

# define PIPE_PAIR 2


extern volatile sig_atomic_t	g_signal;


// * =======================================================>>>>> Shuting down

void	shut_program(t_shell *shell, bool need_msg, int exit_code);
void	free_shell(t_shell *shell);

void	ft_free_tab(char **arr);


// * =======================================================>>>>> String utils

void 	skip_spaces(char *input, int *i);
bool 	ft_isspace(char c);
bool	is_quote(char c);
char	*ultimate_join(char *s1, char *s2);
bool	are_strs_equal(char *s1, char *s2);

char	*ft_strjoin_path(char *dir, char *cmd);


// * =======================================================>>>>> Token utils

void	print_tokens(t_token *tokens); // ! Will be removed later
bool	is_operator(char c);
void	update_token_type(t_token *tokens);
bool	is_operator_type(t_token_type type);
bool	is_redirection_type(t_token_type type);

void	free_tokens(t_token *tokens);
void	add_token(t_shell *shell, t_token **tokens, char *value);
void	advance_token(t_shell *shell);

void	tokenizer(t_shell *shell, char *input);


// * =======================================================>>>>> Syntax checker

bool	check_syntax(t_token *tokens);
bool	are_quotes_closed(t_token *tokens);


// * =======================================================>>>>> Parser utils

void	parser(t_shell *shell);

t_cmd	*new_cmd_node(t_shell *shell);
int		get_len_cmd_args(t_cmd *cmd);
void	free_cmd_list(t_cmd *head);
void	print_cmd_list(t_cmd *head); // ! Will be removed later

t_dir *create_redir_node(t_shell *shell, t_redir_type type, char *filename);
void add_redir_node(t_dir **redir_list, t_dir *new_node);


// * =======================================================>>>>> Environment utils

void	init_env(t_shell *shell, char **envp);
void	free_env(t_env *node);
void	free_env_list(t_env *env);
t_env	*create_env_node(t_shell *shell, char *env_var);
void	add_env_node(t_env **env_list, t_env *new_node);
t_env	*find_env_node(t_env *env, char *key);
char	*get_env_value(t_env *env, char *key);


// * =======================================================>>>>> Expansion utils

char	*load_var_value(t_shell *shell, char *name);
int		measure_len(t_shell *shell, char *s);
char	*parse_var_name(t_shell *shell, char *s, int *i);


// * =======================================================>>>>> Execution utils

void	execution(t_shell *shell);

void	child_process(t_shell *shell, t_cmd *cmd, int i);

int		process_heredocs(t_shell *shell);

int		**setup_pipes(t_shell *shell, int num_pipes);
void	free_pipe_fd(int **pipe_fd, int num);
int		count_pipes(t_cmd *cmd);
void	close_unused_pipes(t_shell *shell, int current);

void	print_open_error(char *filename);
void	print_dir_error(char *cmd);


char	**modify_args(t_cmd *cmd);

bool	cmd_is_dir(char *cmd);


// * =======================================================>>>>> Redirection utils

void	parse_redirection(t_shell *shell, t_cmd *cmd);
bool	setup_redirections_with_pipe(t_shell *shell, t_cmd *cmd, int i);
bool	has_input_redirection_via_list(t_cmd *cmd);
bool	has_output_redirection_via_list(t_cmd *cmd);


// * =======================================================>>>>> Builtin utils

bool	is_builtin(char *cmd);
int		execute_builtin(t_shell *shell, t_cmd *cmd);

int		ft_cd(char **args, t_env *env);
int		ft_echo(char **args);
int		ft_env(t_shell *shell, bool is_export);
int		ft_exit(t_shell *shell, char **args);
int		ft_export(t_shell *shell, char **args);
int		ft_pwd(t_shell *shell);
int		ft_unset(t_shell *shell, char **args);

t_env	*parse_export_argument(t_shell *shell, char *arg);
void	add_or_update_env(t_shell *shell, char *key, char *value);


// * =======================================================>>>>> Path utils

void	path_error_msg(char *cmd, int exit_code, bool is_direct);
char	*get_cmd_path(t_shell *shell, char *cmd, int *exit_code);

#endif
