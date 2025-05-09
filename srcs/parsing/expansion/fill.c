#include "minishell.h"

static void	expand_invalid_var(char *input, char *expanded, t_buffer *buf);
static void expand_invalid_fallback(char *input, char *expanded, t_buffer *buf);
static void	handle_exit_code(t_shell *shell, char *expanded, t_buffer *buf);
static void	handle_valid_var(t_shell *shell, char *input, char *expanded, t_buffer *buf);

// * Expands the variables in the input string, handling different cases
void	fill_vars(t_shell *shell, char *input, char *expanded, t_buffer *buf)
{
	char next;

    next = input[buf->i + 1];
	if (next == '?')
		return handle_exit_code(shell, expanded, buf);
	if (!ft_isalpha(next) && next != '_')
		return expand_invalid_var(input, expanded, buf);
	handle_valid_var(shell, input, expanded, buf);
}

// * Handles the case where the variable is the exit code ("$?")
static void	handle_exit_code(t_shell *shell, char *expanded, t_buffer *buf)
{
	char *str;

	str = ft_itoa(shell->exit_flag);
	if (!str)
		shut_program(shell, true, EX_KO);
	ft_strcpy_to(expanded, str, &(buf->j));
	buf->i += 2;
	free(str);
}

// *	 Handles invalid variables (e.g., digits or unsupported characters after '$')
static void	expand_invalid_var(char *input, char *expanded, t_buffer *buf)
{
    char next;

    next = input[buf->i + 1];
	if (ft_isdigit(next))
	{
		buf->i += 2;
		return ;
	}
    if (!next)
	{
        expanded[buf->j] = '$';
        buf->j += 1;
		buf->i += 1;
		return ;
	}
    if (next == '"' && buf->in_dq)
    {
        expanded[buf->j] = '$';
        buf->j += 1;
        buf->i += 1;
        return ;
    }
    expand_invalid_fallback(input, expanded, buf);
}

// * Handles a special invalid case when the variable follows a quote
static void expand_invalid_fallback(char *input, char *expanded, t_buffer *buf)
{
    char next;

    next = input[buf->i + 1];
    if (next == '"' && !buf->in_dq)
    {
        buf->i += 1;
        return ;
    }
    expanded[buf->j] = input[buf->i];
    expanded[(buf->j) + 1] = input[(buf->i) + 1];
    buf->j += 2;
    buf->i += 2;
}

// * Processes and expands valid variables in the input string
static void	handle_valid_var(t_shell *shell, char *input,
char *expanded, t_buffer *buf)
{
	char	*key;
	char	*val;
	int		start;

	buf->i++;
	start = buf->i;
	while (input[buf->i] && (ft_isalnum(input[buf->i]) || input[buf->i] == '_'))
		buf->i++;
	key = ft_substr(input, start, buf->i - start);
	if (!key)
		shut_program(shell, true, EX_KO);
	val = get_env_value(shell->env, key);
	if (val)
		ft_strcpy_to(expanded, val, &(buf->j));
	free(key);
}
