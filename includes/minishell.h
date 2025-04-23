#ifndef MINISHELL_H
# define MINISHELL_H

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

# include "../libft/libft.h"

# define SHELL_NAME "minishell> "
# define HEREDOC_PROMPT "heredoc> "
# define QUOTE_PROMPT "quote> "
# define DQUOTE_PROMPT "dquote> "

// TODO: Check if we should use specific exit codes
# define EX_OK EXIT_SUCCESS
# define EX_KO EXIT_FAILURE

extern volatile sig_atomic_t	g_signal;

// * ==========================================================>		Enums

// * Enum for token types 
typedef enum	e_token_type
{
    WORD,			// Command or argument
    PIPE,			// '|'
    REDIRECT_IN,	// '<'
    REDIRECT_OUT,	// '>'
    HEREDOC,		// '<<'
    APPEND,			// '>>'
    DQUOTE,			// Double quote
	SQUOTE,			// Single quote
	NIL				// NULL (default)
}				t_token_type;


// * ==========================================================>		Structures

// * Struct for buffer in order to prevent norm forbids
typedef struct s_buffer
{
	int		i;
	int		j;
	int		k;
}	t_buffer;


// * Struct for environment variables
typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}               t_env;

// * Struct for command arguments
typedef struct s_cmd
{
    char            **args;
    int             in_fd;
    int             out_fd;
	char			*heredoc_delim; // !
	// int			heredoc_fd;
	bool			has_heredoc; // !
    struct s_cmd   *next;
}               t_cmd;

// * Struct for tokens
typedef struct s_token
{
	char            *value;
    t_token_type    type;
	struct s_token  *next;
}               t_token;

// * Struct for shell state
typedef struct s_shell
{
	char			*input;
	char			**og_env;
	int				exit_flag;
	int				num_pipes;
	t_env           *env;
	t_cmd           *cmd;
	t_token			*token;
}               t_shell;

// * ==========================================================>		Built-ins
int     	ft_cd(char **args);
int     	ft_echo(char **args);
int     	ft_env(t_shell *shell);
int     	ft_exit(char **args);
int			ft_export(t_shell *shell, char **args);
int     	ft_pwd(void);
int     	ft_unset(t_shell *shell, char **args);

// * ==========================================================>		Execution
int			exec_cmd(t_shell *shell, t_cmd *cmd);
int			**handle_pipe(t_shell *shell, t_cmd *cmd, int num_pipes);

// int     is_builtin(char *cmd);
// void    run_builtin(t_cmd *cmd);

// * ==========================================================>		Parsing

void 		print_tokens(t_token *tokens);		// ! (DEBUG)
void 		print_cmd_list(t_cmd *cmd);			// ! (DEBUG)

t_token 	*tokenizer(char *input);
t_cmd   	*parse_input(t_shell *shell);
// char    **lexer(char *input);
// int     syntax_checker(char **tokens);
// t_cmd   *build_ast(t_token *tokens);

// * Redirections & Pipes
// int     handle_redirections(t_cmd *cmd);
// int     setup_pipes(t_cmd *cmd);

// * ==========================================================>		Environment management
void		init_env(t_shell *shell, char **envp);
// char    *get_env_value(char *key);
// void    set_env_value(char *key, char *value);
// void    add_env_var(char *key, char *value);
// void    remove_env_var(char *key);

// * ==========================================================>		Signals
// void    handle_signals(void);
// void    sigint_handler(int signo);
// void    sigquit_handler(int signo);

// * ==========================================================>		Utilities

bool		ft_isspace(char c);
bool		are_strs_equal(char *s1, char *s2);
void		skip_spaces(char *input, int *i);
bool	    is_operator(char c);
int			is_numeric(const char *str);
bool		is_quote(char c);
char		*ultimate_join(char *s1, char *s2);

void		init_env(t_shell *shell, char **envp);
t_env		*find_env_node(t_env *list, char *key);
char		*get_env_value(t_env *env, char *key);
void		free_env(t_env *env);
void	add_env_node(t_env **env_list, t_env *new_node);

void		handle_error(const char *message, int exit_status);

void	expander(t_shell *shell);

char 		**refill_cmd_args(char **old, int len, char *value);
void		init_cmd(t_cmd *cmd);
void		add_token(t_token **tokens, char *value);

int			count_pipes(t_cmd *cmd);
int			**handle_pipe(t_shell *shell, t_cmd *cmd, int num_pipes);
void        close_pipes(int **pipe_fd, int num_pipes);
int			exec_builtin(t_shell *shell, char **args);
int			is_builtin(char *cmd);

int			ft_open_file(char *file_name, int flow);
char		*ft_find_envp(char **envp);
char		*ft_find_cmd(char *cmd, char **envp);

bool		is_quote_open(char input[]);



// * ==========================================================>		Freeing functions

void	ft_free_tab(char **tab);
void    free_env(t_env *env);
void    free_cmd(t_cmd *cmd);
void    free_tokens(t_token *token);
void    free_shell(t_shell *shell);


// * ==========================================================>	 Expander Utils

void	fill_new_value(char *src, char *dst, int *j);
void	extract_braced_var_name(const char *s, int *i, char *var_name);
void	extract_var_name(const char *s, int *i, char *var_name);
int		measure_expanded_length(const char *s, t_shell *shell);
bool	is_var_char(char c);
void 	fill_expanded_string_helper(t_shell *shell, char *src, char *dst, t_buffer *buf);
bool is_in_single_quotes(const char *str, int pos);

#endif
