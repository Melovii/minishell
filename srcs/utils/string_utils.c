#include "minishell.h"

// * Function to check if a character is whitespace
bool ft_isspace(char c)
{
	if (c == '\0')
		return (false);
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f')
		return (true);
	return (false);
}

// * Function to skip spaces
void skip_spaces(char *input, int *i)
{
	if (!input)
		return ;	// TODO: Add error message
    while (input[*i] && ft_isspace(input[*i]))
        (*i)++;
}

bool	are_strs_equal(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (false);
	if (ft_strlen(s1) == ft_strlen(s2) && ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
		return (true);
	return (false);
}

// * Function to check if a string is numeric
int	is_numeric(const char *str)
{
	int i = 0;

	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
