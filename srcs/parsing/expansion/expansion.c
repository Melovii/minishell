#include "minishell.h"
#include "../libft/libft.h"

static void	init_buf(t_buffer *buf);
static void	fill_expanded_string(t_shell *shell, char *input, char *expanded);

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

static void	fill_expanded_string(t_shell *shell, char *input, char *expanded)
{
	t_buffer	buf;

	init_buf(&buf);
	while (input[buf.i])
	{
		if (input[buf.i] == '"' && !buf.in_sq)
		{
			buf.in_dq = !buf.in_dq;
			expanded[buf.j++] = input[buf.i];
		}
		else if (input[buf.i] == '\'' && !buf.in_dq)
		{
			buf.in_sq = !buf.in_sq;
			expanded[buf.j++] = input[buf.i];
		}
		else if (input[buf.i] == '$' && !buf.in_sq)
		{
			fill_vars(shell, input, expanded, &buf);
			continue;
		}
		else
			expanded[buf.j++] = input[buf.i];
		buf.i++;
	}
	expanded[buf.j] = '\0';
}


static void	init_buf(t_buffer *buf)
{
	buf->i = 0;
	buf->j = 0;
	buf->k = 0;
	buf->in_dq = false;
	buf->in_sq = false;
}
