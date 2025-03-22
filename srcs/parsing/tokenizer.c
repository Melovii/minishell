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

// * Function to parse quoted tokens and add them to the token list
static int	get_quoted_token(char *input, int *i, t_token **tokens)
{
	char	quote;
	int		start;
	char	*substr;

	quote = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
		return (0);
	(*i)++;
	substr = ft_substr(input, start, (*i) - start - 1);
	if (!substr)
		return (0);
	add_token(tokens, substr);
	free(substr);
	return (1);
}

// * Function to parse and add word tokens (non-whitespace, non-special characters) to the token list
static int	get_word_token(char *input, int *i, t_token **tokens)
{
	int	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
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
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
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
void print_tokens(t_token *tokens)
{
    printf("Tokens:\n");
    while (tokens)
    {
        printf("  - \"%s\"\n", tokens->value);
        tokens = tokens->next;
    }
}
