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
	int		i;
	int		j;
	bool	in_double;
	bool	in_single;

	i = 0;
	j = 0;
	in_double = false;
	in_single = false;
	while (input[i])
	{
		if (input[i] == '"')
			fill_dq_state(shell, input, expanded, &in_double, &i, &j);
	}
	expanded[j] = '\0';
}

static void fill_dq_state(t_shell *shell, char *input, char *expanded, bool *in_double, int *i, int *j)
{
	*in_double = !(*in_double);
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			fill_vars(shell, input, expanded, i, j, in_double);
		}
		else
		{
			expanded[*j] = input[*i];
			(*i)++;
			(*j)++;
		}
	}

}


// static void fill_vars(t_shell *shell, char *input, char *expanded, int *i, int *j, bool *in_double)
// {
// 	if ()
// }