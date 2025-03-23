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
    struct s_cmd   *next;
}               t_cmd;

// * Struct for tokens
typedef struct s_token
{
	char            *value;
	struct s_token  *next;
}               t_token;

// * Struct for shell state
typedef struct s_shell
{
	int				exit_flag;
	t_env           *env;
	t_cmd           *cmd;
	t_token			*token;
}               t_shell;

// * ==========================================================>		Built-ins
int     	ft_cd(char **args);
// int     	ft_echo(char **args);
int     	ft_env(t_shell *shell);
int     	ft_exit(char **args);
// int     	ft_export(t_shell *shell, char **args);
int     	ft_pwd(void);
// int     	ft_unset(t_shell *shell, char **args);

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
// void    free_env(void);

// * ==========================================================>		Signals
// void    handle_signals(void);
// void    sigint_handler(int signo);
// void    sigquit_handler(int signo);

// * ==========================================================>		Utilities
bool		ft_isspace(char c);
bool		are_strs_equal(char *s1, char *s2);
void		skip_spaces(char *input, int *i);
int			is_numeric(const char *str);

void		init_env(t_shell *shell, char **envp);

void		handle_error(const char *message, int exit_status);

char 		**refill_cmd_args(char **old, int len, char *value);
void		init_cmd(t_cmd *cmd);
void		add_token(t_token **tokens, char *value);

int			count_pipes(t_cmd *cmd);
int			**handle_pipe(t_shell *shell, t_cmd *cmd, int num_pipes);
void        close_pipes(int **pipe_fd, int num_pipes);
int			exec_builtin(t_shell *shell, char **args);
int			is_builtin(char *cmd);

// void    free_cmd(t_cmd *cmd);
// void    free_tokens(t_token *token);
// void    free_shell(t_shell *shell);

#endif
