#include "minishell.h"

void fill_expanded_string_helper(t_shell *shell, char *src, char *dst, t_buffer *buf)
{
	char var_name[256];
	char *value;
	if (buf->k == 1)
	{
		extract_var_name(src, &(buf->i), var_name);
		value = get_env_value(shell->env, var_name);
		if (value)
			fill_new_value(value, dst, &(buf->j));
	}
	else if (buf->k == 2)
	{
		extract_braced_var_name(src, &(buf->i), var_name);
		value = get_env_value(shell->env, var_name);
		if (value)
			fill_new_value(value, dst, &(buf->j));
	}
	buf->k = 1;
}

void extract_braced_var_name(const char *s, int *i, char *var_name)
{
	int k;

	k = 0;
	(*i)++; // Skip the '{'
	while (s[*i] && s[*i] != '}' && k < 255)
	{
		var_name[k++] = s[*i];
		(*i)++;
	}
	if (s[*i] == '}')
		(*i)++;
	var_name[k] = '\0';
}

void extract_var_name(const char *s, int *i, char *var_name)
{
	int k;

	k = 0;
	while (s[*i] && is_var_char(s[*i]) && k < 255)
	{
		var_name[k++] = s[*i];
		(*i)++;
	}
	var_name[k] = '\0';
}

bool is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
