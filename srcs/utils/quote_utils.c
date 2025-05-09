#include "minishell.h"

static bool	is_token_quote_balanced(char *str);

// * Checks if all quotes in the token are balanced (i.e., properly closed)
bool	are_quotes_closed(t_token *tokens)
{
	while (tokens)
	{
		if (!is_token_quote_balanced(tokens->value))
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `newline'", STDERR_FILENO);
			return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}	

// * Checks if a string contains either single or double quotes
bool does_included_quote(char *str)
{
    size_t i = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
            return (true);
        i++;
    }
    return (false);
}

// * Checks if the quotes in a token are balanced (paired and closed)
static bool	is_token_quote_balanced(char *str)
{
	int		i;
	char	quote;

	quote = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (quote == '\0')
				quote = str[i];
			else if (quote == str[i])
				quote = '\0';
		}
		i++;
	}
	return (quote == '\0');
}
