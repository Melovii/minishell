#include "minishell.h"

// * Function to parse special tokens ('<' and '>') and add them to the token list
static int	get_special_token(char *input, int *i, t_token **tokens)
{
	char	symbol[3];

	symbol[0] = input[*i];
	symbol[1] = 0;
	symbol[2] = 0;
	if ((input[*i] == '<' || input[*i] == '>') && input[*i + 1] == input[*i])
		symbol[1] = input[++(*i)];
	add_token(tokens, symbol);
	(*i)++;
	return (1);
}

static char	*get_quote_part(char *input, int *i, char **combined)
{
	int		start;
	char	*new;
	char	quote;

	quote = input[(*i)++];
	start = *i - 1;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])  // ! This code logic is wrong
	{
		free(*combined);
		handle_error(NULL, 1); // * If this block executed that means Some quotes are open
	}
	(*i)++;
	new = ft_substr(input, start, (*i) - start);
	if (!new)
	{
		free(*combined);
		handle_error(NULL, 1); // * If this block executed that means Some quotes are open
	}
	return (new);
}

static char	*get_default_part(char *input, int *i, char **combined)
{
	int		start;
	char	*new;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
		(*i)++;
	new = ft_substr(input, start, (*i) - start);
	if (!new)
	{
		free(*combined);
		handle_error(NULL, 1); // * If this block executed that means Some quotes are open
	}
	return (new);
}

static int	get_combined_token(char *input, int *i, t_token **tokens)
{
	char	*combined;
	char	*part;

	combined = ft_strdup("");
	if (!combined)
		handle_error(NULL, 1); // ! Check Later
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
	{
		if (is_quote(input[*i]))
			part = get_quote_part(input, i, &combined);
		else
			part = get_default_part(input, i, &combined);
		combined = ultimate_join(combined, part);
		if (!combined)
			handle_error(NULL, 1); // * If this block executed that means Some quotes are open
	}
	add_token(tokens, combined);
	free(combined);
	return (1);
}

// * Function to tokenize the input string into a linked list of tokens
t_token	*tokenizer(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			get_special_token(input, &i, &tokens);
		else
			get_combined_token(input, &i, &tokens);
	}
	return (tokens);
}

// !(DEBUG) Function to print all the tokens in the token list
void	print_tokens(t_token *tokens)
{
	printf("Tokens:\n");
	while (tokens)
	{
		printf("  - \"%s\"\n", tokens->value);
		tokens = tokens->next;
	}
}
