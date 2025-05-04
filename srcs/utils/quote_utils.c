#include "minishell.h"


static bool	is_token_quote_balanced(char *str);

bool	are_quotes_closed(t_token *tokens)
{
	while (tokens)
	{
		if (!is_token_quote_balanced(tokens->value))
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
			return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}

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
