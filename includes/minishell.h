#ifndef MINISHELL_H
#define MINISHELL_H

// * =======================================================>>>>> Standard Library Includes

// TODO: Remove unused includes (check with clang-tidy)
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
// # include <sys/types.h>
// # include <dirent.h>
// # include <ctype.h>
// # include <stdio.h>


// * =======================================================>>>>> Local Includes

# include "../libft/libft.h"
# include "structs.h"
# include "sh_signals.h"
# include "sh_env.h"
# include "sh_tokenizer.h"
# include "sh_builtin.h"
# include "sh_parser.h"
# include "sh_exec.h"
# include "sh_utils.h"
# include "sh_expansion.h"

// * =======================================================>>>>> Macros

// Exit status codes
# define EX_OK EXIT_SUCCESS
# define EX_KO EXIT_FAILURE

// Prompts
# define PROMPT "minishell> "
# define HEREDOC_PROMPT "heredoc> "

// Heredoc error codes
# define HEREDOC_PIPE_ERROR 1
# define HEREDOC_FORK_ERROR 2
# define HEREDOC_EXIT_INTERRUPTED 130

# define INV_ARGC 2

# define PIPE_PAIR 2

#endif
