#ifndef MINISHELL_H
# define MINISHELL_H

// * ======================================================= >>>>> Standard Library Includes

// TODO: Remove unused includes (check with clang-tidy)
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
// # include <sys/types.h>
// # include <dirent.h>
// # include <ctype.h>
// # include <stdio.h>

// * ======================================================= >>>>> Local Includes

# include "../libft/libft.h"
# include "sh_builtin.h"
# include "sh_env.h"
# include "sh_exec.h"
# include "sh_expansion.h"
# include "sh_parser.h"
# include "sh_signals.h"
# include "sh_tokenizer.h"
# include "sh_utils.h"
# include "structs.h"

// * ======================================================= >>>>> Macros

// Exit status codes
# define EX_OK EXIT_SUCCESS
# define EX_KO EXIT_FAILURE
# define NOT_FOUND 127
# define NO_PERM 126

// Prompts
# define PROMPT "minishell> "
# define HEREDOC_PROMPT "heredoc> "

// Heredoc error codes
# define HEREDOC_PIPE_ERROR 1
# define HEREDOC_FORK_ERROR 2

# define WRITE_END 1
# define READ_END 0

# define INV_ARGC 2

# define PIPE_PAIR 2

# define SYN_ERR_MSG_1 "minishell: syntax error near unexpected token `newline'"

#endif
