#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>

// * ==========================================================>		Enums

// * Enum for token types 
typedef enum	e_token_type
{
    WORD,			// Command or argument
    INV_OPERATOR,	// Invalid operator
    PIPE,			// '|'
    REDIRECT_IN,	// '<'
    REDIRECT_OUT,	// '>'
    HEREDOC,		// '<<'
    APPEND,			// '>>'
	NIL				// NULL (default)

}				t_token_type;

// * Enum for redirection types
typedef enum e_redir_type
{
    DIR_IN,     // '<'
    DIR_OUT,    // '>'
    DIR_APPEND, // '>>'
    DIR_HEREDOC // '<<'

}   t_redir_type;

// * ==========================================================>		Structures

// * Struct for buffer in order to prevent norm forbids
typedef struct s_buffer
{
	int		i;
	int		j;
	int		k;
}	t_buffer;

// * Struct for redirection
typedef struct s_dir
{
    t_redir_type    type;
    char            *filename;      // infile, outfile, delimiter (for heredoc)
    int             heredoc_fd[2];  // only for heredoc
    struct s_dir    *next;
}               t_dir;

// * Struct for environment variables
typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}               t_env;

// * Struct for tokens
typedef struct s_token
{
	char            *value;
    t_token_type    type;
	struct s_token  *next;
}               t_token;

// * Struct for command arguments
typedef struct s_cmd
{
    t_token		    *args;

    int             in_fd;
    int             out_fd;

    t_dir           *redir_list;    // redirection queue

    struct s_cmd    *next;
}               t_cmd;

// * Struct for shell state
typedef struct s_shell
{
	char			*input;
	char			**og_env;
	int				exit_flag;
    int             number_of_prompts;
	int				num_pipes;
    int             **num_pipes_fd;
	t_env           *env;
	t_cmd           *cmd;
	t_token			*token;
}               t_shell;

#endif
