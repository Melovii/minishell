#include "minishell.h"

static int	determine_len(char *input, int *i);
static void	fill_pure_token(char *input, int *i, char *token);

// * purpose: tokenizing default input
// * parameters:	(shell)-> main struct, (input)-> str from client
// *				(i/index)-> current input index
// *				(value)-> is it come from another function or is it token start
// TODO: Tokenize Deafult
char	*token_default(t_shell *shell, char *input, int *i, char *token)
{
	if (!token)
	{
		token = ft_calloc(determine_len(input, i) + 1, sizeof(char));
		if (token == NULL)
			shut_program_err(shell);
	}
	fill_pure_token(input, i, token);
	// TODO: add interactive mode + quote statements
	if (is_quote(input[(*i) + 1]))
		return (concat_quote(shell, input, i, token));
	return (token);
}

char *concat_default(t_shell *shell, char *input, int *i, char *token)
{
	char *added;

	added = ft_calloc(determine_len(input, i) + 1, sizeof(char));
	if (!added)
		shut_program_err(shell);
	fill_pure_token(input, i, added);
	token = ultimate_join(shell, token, added);
	if (is_quote(input[(*i) + 1]))
		return (concat_quote(shell, input, i, token));
	return (token);
}

static void	fill_pure_token(char *input, int *i, char *token)
{
	int	j;
	int	len;

	j = 0;
	len = determine_len(input, i);
	while (j < len)
	{
		token[j] = input[*i];
		j++;
		(*i) += 1;
	}
	(*i) -= 1; // for proper index
	token[j] = '\0';
}

// * purpose: 		determining the length of the token (without quotes)
// * parameters:	(input)-> client input, (*i/index)->> current cursor index
static int	determine_len(char *input, int *i)
{
	int	j;
	int	len;

	j = *i;
	len = 0;
	while (!(is_operator(input[j]) || is_quote(input[j]) || input[j] == SPACE
			|| input[j] == '\0'))
	{
		j++;
		len++;
	}
	return (len);
}
