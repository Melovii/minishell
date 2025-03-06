#include "minishell.h"

static int	determine_len(char *input, int *i, char quote_type);
static void	fill_pure_token(char *input, int *i, char *token, char quote_type);

// * purpose: tokenizing double and single quotes and return the token value
// * parameters:	(shell)-> main struct, (input)-> str from client
// *				(i/index)-> current input index
// TODO: Tokenize Double and Single Quotes
char 	*token_quote(t_shell *shell, char *input, int *i, char *token)
{
	if (!token)
	{
		token = ft_calloc(determine_len(input, i, input[*i]) + 1, sizeof(char));
		if (!token)
			shut_program_err(shell);
	}
	fill_pure_token(input, i, token, input[*i]);
	// TODO: add interactive mode + quote statements
	if (is_quote(input[(*i) + 1]))
		return (concat_quote(shell, input, i, token));
	else if (ft_isalnum(input[(*i) + 1]))
		return (concat_default(shell, input, i, token));
	return (token);
}

char *concat_quote(t_shell *shell, char *input, int *i, char *token)
{
	char *added;
	char	quote_type;

	(*i) += 1;
	quote_type = input[*i];
	added = ft_calloc(determine_len(input, i, quote_type) + 1, sizeof(char));
	if (!added)
		shut_program_err(shell);
	fill_pure_token(input, i, added, quote_type);
	token = ultimate_join(shell, token, added);
	if (is_quote(input[(*i) + 1]))
		return (concat_quote(shell, input, i, token));
	if (ft_isalnum(input[(*i) + 1]))
		return (concat_default(shell, input, i, token));
	return (token);
}


static void	fill_pure_token(char *input, int *i, char *token, char quote_type)
{
	int	j;
	int	len;

	j = 0;
	len = determine_len(input, i, quote_type);
	(*i) += 1;
	while (j < len)
	{
		token[j] = input[*i];
		j++;
		(*i) += 1;
	}
	 // for proper index
	token[j] = '\0';
}

// * purpose: 		determining the length of the token (without quotes)
// * parameters:	(input)-> client input, (*i/index)->> current cursor index
// * tests:			"ali" -> 3,      "ali -> 3,  
static int	determine_len(char *input, int *i, char quote_type)
{
	int	len;
	int	j;

	len = 0;
	j = *i + 1;
	while (input[j])
	{
		if (input[j] == quote_type)
			return (len);
		len++;
		j++;
	}
	return (len);
}
