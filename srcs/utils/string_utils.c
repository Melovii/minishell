#include "minishell.h"

// * Function to check if a character is whitespace
int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

// * Function to skip spaces
void skip_spaces(char *input, int *i)
{
    while (input[*i] && ft_isspace(input[*i]))
        (*i)++;
}

bool	is_strs_equals(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2) && ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
		return (true);
	return (false);
}
