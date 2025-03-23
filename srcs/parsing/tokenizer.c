#include "minishell.h"

//* Function to parse special tokens ('<' and '>') and add them to the token list
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

// * Function to parse quoted tokens and add them to the token list
static int	get_quoted_token(char *input, int *i, t_token **tokens)
{
	char	quote;
	int		start;
	int		len;
	char	*substr;
	char	*combined;
	int		j;

	quote = input[(*i)++];
	start = *i;

	// Find the closing quote
	while (input[*i] && input[*i] != quote)
		(*i)++;

	if (!input[*i]) // If no closing quote is found, return error
		return (0);

	len = (*i) - start;
	substr = ft_substr(input, start, len);
	if (!substr)
		return (0);
	(*i)++; // Move past the closing quote

	// Concatenate the next characters if they're not space or operator
	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
		(*i)++;

	if (*i > start) // If there is an additional part after the quote
	{
		combined = malloc(len + (*i - start) + 1);
		if (!combined)
			return (0);
		strcpy(combined, substr);
		j = 0;
		while (start < *i)
			combined[len++] = input[start++];
		combined[len] = '\0';
		add_token(tokens, combined);
		free(combined);
	}
	else
		add_token(tokens, substr); // Otherwise, just add the quoted part

	free(substr);
	return (1);
}



// * Function to parse and add word tokens (non-whitespace, non-special characters) to the token list
static int	get_word_token(char *input, int *i, t_token **tokens)
{
	int	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
		(*i)++;
	add_token(tokens, ft_substr(input, start, (*i) - start));
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
		if (is_operator(input[i]))
			get_special_token(input, &i, &tokens);
		else if (input[i] == '"' || input[i] == '\'')
			get_quoted_token(input, &i, &tokens);
		else
			get_word_token(input, &i, &tokens);
		skip_spaces(input, &i);
	}
	return (tokens);
}

// !(DEBUG) Function to print all the tokens in the token list
void	print_tokens(t_token *tokens)
{
	printf("Tokens:\n");
	while (tokens)
	{
		printf("  - %s\n", tokens->value);
		tokens = tokens->next;
	}
}
