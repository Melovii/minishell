#include "minishell.h"

static void	fill_expanded_string(char *src, char *dst, t_shell *shell);
static char	*expand_value(char *old, t_shell *shell);
static bool	does_have_vars(char *value);

void	expander(t_shell *shell)
{
	t_token	*token_list;
	char	*temp;

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

static char	*expand_value(char *old, t_shell *shell)
{
	int	final_length;
	char	*new_str;

	final_length = measure_expanded_length(old, shell);
	new_str = malloc(final_length + 1);
	if (!new_str)
		return (NULL);
	fill_expanded_string(old, new_str, shell);
	return (new_str);
}

static void	fill_expanded_string(char *src, char *dst, t_shell *shell)
{
	int	i;
	int	j;
	char	var_name[256];
	char	*value;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '$')
		{
			i++;
			if (src[i] && src[i] == '{')
			{
				extract_braced_var_name(src, &i, var_name);
				value = get_env_value(shell->env, var_name);
				if (value)
				{
					size_t k = 0;
					while (value[k])
						dst[j++] = value[k++];
				}
			}
			else if (src[i] && is_var_char(src[i]))
			{
				extract_var_name(src, &i, var_name);
				value = get_env_value(shell->env, var_name);
				if (value)
				{
					size_t k = 0;
					while (value[k])
						dst[j++] = value[k++];
				}
			}
			else
				dst[j++] = '$';
		}
		else
			dst[j++] = src[i++];
	}
	dst[j] = '\0';
}

static bool	does_have_vars(char *value)
{
	if (ft_strchr(value, '$'))
		return (true);
	return (false);
}

