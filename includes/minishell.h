#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34

// TODO: fix why this is not recognised in signal.c
// # define _XOPEN_SOURCE 700
// # define _POSIX_C_SOURCE 200809L

typedef enum e_bool
{
    C_TRUE = 1,
    C_FALSE = 0

}   t_bool;

// * Token types for lexing
typedef enum e_token_type
{
    TK_WORD,       	// Command or argument
    TK_PIPE,       	// '|'
    TK_RED_IN,   	// '<'
    TK_RED_OUT,  	// '>'
    TK_APPEND,     	// '>>'
    TK_HEREDOC,    	// '<<'
    TK_ENV_VAR,		// '$VAR'
    TK_AND,  		// '&&'
    TK_OR,   		// '||'
    TK_EOF          // End of file/input
}	t_token_type;

// * Struct for tokens (Lexing)
typedef struct s_token
{
    t_token_type 	type;	// Type of token
    char         	*value;	// Token value (e.g., "ls", "-l", "|")
    struct s_token 	*next;
}	t_token;

// * Command structure
typedef struct s_command
{
    char	 			**argv;		// Command arguments ["ls", "-l", NULL] etc.
    char 				*path;		// Command path
	char				*in_file;	// "< file"
	char				*out_file;	// "> file" or ">> file"
	int					fd_in;
	int					fd_out;
	t_bool				append;		// Append mode for ">>"
	t_bool				is_builtin;
	struct s_command	*next;
}   t_command;

// * Environment variable storage (for export)
typedef struct s_env
{
	char			*key;	// Environment variable name
	char			*value;	// Environment variable value
	struct s_env	*next;	// Next variable
}	t_env;

// * Shell state structure (Global shell context)
typedef struct s_shell
{
	t_command		*cmd_list;		// Linked list of commands
	t_env			*env_list;		// Linked list of environment variables
	char			**envp;			// Copy of environment variables
	t_bool			is_interactive;	// Whether shell is running interactively
}	t_shell;

// ! FUNCTION PROTOTYPES

// * Lexing
// process_input(input);

// * Execution

// * Builtins

// * Environment

// * Signals
void setup_signals(void);

// * Utils

#endif
