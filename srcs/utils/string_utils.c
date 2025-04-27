#include "minishell.h"
#include "../libft/libft.h"

bool	are_strs_equal(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (false);
	if (ft_strlen(s1) == ft_strlen(s2) && ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
		return (true);
	return (false);
}

// * Function to check if a character is whitespace
bool ft_isspace(char c)
{
	if (c == '\0')
		return (false);
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f')
		return (true);
	return (false);
}

void skip_spaces(char *input, int *i)
{
	if (!input)
		return ;
    while (input[*i] && ft_isspace(input[*i]))
        (*i)++;
}

bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

char	*ultimate_join(char *s1, char *s2)
{
	char	*ultimate;

	if (!s1 | !s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ultimate = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (!ultimate)
		return (NULL);
	return (ultimate);
}

