#include "minishell.h"

static void fill_expanded_string(char *src, char *dst, t_shell *shell);
static char *expand_value(char *old, t_shell *shell);
static bool does_have_vars(char *value);

void expander(t_shell *shell)
{
	t_token *token_list;
	char *temp;

	token_list = shell->token;
	while (token_list)
	{
		if (token_list->value && does_have_vars(token_list->value))
		{
			temp = token_list->value;
			token_list->value = expand_value(token_list->value, shell);
			free(temp);
		}
		token_list = token_list->next;
	}
}

static char *expand_value(char *old, t_shell *shell)
{
	int final_length;
	char *new_str;

	final_length = measure_expanded_length(old, shell);
	new_str = ft_calloc(final_length + 1, sizeof(char));
	if (!new_str)
		return (NULL); // ! Handle memory allocation error
	fill_expanded_string(old, new_str, shell);
	return (new_str);
}

static void fill_expanded_string(char *src, char *dst, t_shell *shell)
{
	t_buffer buf;

	buf.i = 0;
	buf.j = 0;
	buf.k = 1;
	while (src[buf.i])
	{
		if (src[buf.i] == '$' && !is_in_single_quotes(src, buf.i))
		{
			(buf.i)++;
			if (src[buf.i] && src[buf.i] == '{')
			{
				buf.k = 2;
				fill_expanded_string_helper(shell, src, dst, &buf);
			}
			else if (src[buf.i] && is_var_char(src[buf.i]))
				fill_expanded_string_helper(shell, src, dst, &buf);
			else
				dst[(buf.j)++] = '$';
		}
		else
			dst[(buf.j)++] = src[(buf.i)++];
	}
	dst[buf.j] = '\0';
}

static bool does_have_vars(char *value)
{
	if (ft_strchr(value, '$'))
		return (true);
	return (false);
}

bool is_in_single_quotes(const char *str, int pos)
{
	int i = 0;
	bool in_single = false;
	bool in_double = false;

	while (str[i] && i <= pos)
	{
		if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		i++;
	}
	return (in_single);
}
