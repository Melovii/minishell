#include "minishell.h"

static void	tokenise_input(t_shell *shell, char *input)
{
	// TODO:
	// Control default input that without operators and quotes
	// Control ' and "  ---> by using sub-functions
	// Control operators ('|', '>>', '<<', '>', '<')
	// Split arguments and return tokenised linked list.
	// final process

	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == SPACE)
			continue ;
		else if (is_operator(input[i]))
			token_operator(shell, input, &i);
		else if (is_quote(input[i]))
		{
			cr_add_token(shell, &(shell->token_list), 
				token_quote(shell, input, &i, NULL), TK_WORD);
		}
		else
			cr_add_token(shell, &(shell->token_list), 
				token_default(shell, input, &i, NULL), TK_WORD);
	}
}

// ? Example: ["ls", "-l", "|", "grep", "minishell", ">", "output.txt"]

void	clear_heredoc(t_shell *shell); // ? add later


// ! only exist for testing will be deleted
const char *get_token_type_name(t_token_type type);
void display_tokens(t_token *head)
{
    while (head)
    {
        printf("Type: %-12s | Value: %s\n", 
            get_token_type_name(head->type), 
            (head->value && head->value[0] != '\0') ? head->value : "\"\""
        );
        head = head->next;
    }
}

const char *get_token_type_name(t_token_type type)
{
    switch (type)
    {
    case TK_WORD:
        return "WORD";
    case TK_PIPE:
        return "PIPE";
    case TK_RED_IN:
        return "REDIRECT_IN";
    case TK_RED_OUT:
        return "REDIRECT_OUT";
    case TK_APPEND:
        return "APPEND";
    case TK_HEREDOC:
        return "HEREDOC";
    case TK_ENV_VAR:
        return "ENV_VAR";
    case TK_EOF:
        return "EOF";
    default:
        return "UNKNOWN";
    }
}

void	process_input(t_shell *shell)
{
	while (is_interactive(shell))
		handle_interactive(shell);
	shell->is_interactive = C_FALSE;
	add_history(shell->history);
	clear_heredoc(shell);
	shell->heredoc_list = NULL;  //! clear the  heredoc_list after the finish execution
	shell->heredoc_index = 0;	// ! same as above
	printf("%s\n", shell->input);
	tokenise_input(shell, shell->input);
	display_tokens(shell->token_list);
	shell->token_list = NULL; // ! only for testing it causes leak
	// TODO: Create command linked list
	// TODO: Execute command
}

// ? find correct file for these functions

void	clean_one_heredoc(t_heredoc *node)
{
	unlink(node->file_name);
	free(node->file_name);
	free(node->limiter);
	free(node);
}

void	clear_heredoc(t_shell *shell)
{
	t_heredoc *heredoc_head;
	t_heredoc *temp;

	heredoc_head = shell->heredoc_list;
	while (heredoc_head)
	{
		temp = heredoc_head->next;
		clean_one_heredoc(heredoc_head);
		heredoc_head = temp;
	}
}