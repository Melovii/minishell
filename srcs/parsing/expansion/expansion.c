#include "minishell.h"
#include "../libft/libft.h"

static void fill_vars(int *i, int *j, bool *in_double, bool *in_single);
static void	fill_expanded_string(t_shell *shell, char *input, char *expanded);
static int	handle_variable(t_shell *shell, char *input, char *res, int *i, int j);

char	*expand_vars( t_shell *shell, char *input)
{
	int		len;
	char	*expanded;

	len = measure_len(shell, input);
	expanded = ft_calloc(len + 1, sizeof(char));
	if (!expanded)
    {
		shut_program(shell, true, EX_KO);
    }
	fill_expanded_string(shell, input, expanded);
	free(input);
	if (expanded[0] == '\0')
	{
		free(expanded);
		return (NULL);
	}
	return (expanded);
}

static void fill_expanded_string(t_shell *shell, char *input, char *expanded)
{
    int i;
    int j;
    bool in_single_quote;
    bool in_double_quote;

	fill_vars(&i, &j, &in_double_quote, &in_single_quote);
    while (input[i])
    {
        if (input[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            expanded[j++] = input[i++];
        }
        else if (input[i] == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            expanded[j++] = input[i++];
        }
        else if (input[i] == '$' && input[i + 1] && input[i + 1] != '"' && !in_single_quote)
            j = handle_variable(shell, input, expanded, &i, j);
        else
            expanded[j++] = input[i++];
    }
    expanded[j] = '\0';
}


static int	handle_variable(t_shell *shell, char *input, char *res, int *i, int j)
{
	char	*var_name;
	char	*var_value;
	int		len;

	(*i)++;
	var_name = parse_var_name(shell, input, i);
	if (!var_name || var_name[0] == '\0')
	{
		free(var_name);
		return (j);
	}
	var_value = load_var_value(shell, var_name);
	if (var_value)
	{
		len = ft_strlen(var_value);
		ft_memcpy(res + j, var_value, len);
		j += len;
		free(var_value);
	}
	free(var_name);
	return (j);
}

static void fill_vars(int *i, int *j, bool *in_double, bool *in_single)
{
	*i = 0;
	*j = 0;
	*in_double = false;
	*in_single = false;
}
