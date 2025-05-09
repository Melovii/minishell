#ifndef SH_TOKENIZER_H
# define SH_TOKENIZER_H

# include "structs.h"

// * =======================================================>>>>> Token Handling

void	advance_token(t_shell *shell);
void	update_token_type(t_token *tokens);
void	tokenizer(t_shell *shell, char *input);
void	add_token(t_shell *shell, t_token **tokens, char *value);

// * =======================================================>>>>> Helpers

void	free_tokens(t_token *tokens);
void	free_token_node(t_token *node);

bool	is_operator(char c);
bool	is_operator_type(t_token_type type);
bool	is_redirection_type(t_token_type type);

#endif
