#include "minishell.h"

static bool	does_have_vars(char *value);
char		*expand_value(char *old);

void	expander(t_shell *shell)
{
	t_token	*token_list;
	char	*value;

	token_list = shell->token;
	while (token_list)
	{
		if (token_list->value && does_have_vars(token_list->value))
			token_list->value = expand_value(token_list->value);
		token_list = token_list->next;
	}
}

char	*expand_value(char *old)
{
	// ! Check later
}

static bool	does_have_vars(char *value)
{
	if (ft_strchr(value, '$'))
		return (true);
	return (false);
}
