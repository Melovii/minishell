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
