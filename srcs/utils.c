#include "minishell.h"

t_bool are_strs_equal(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (C_FALSE);
	if ((ft_strlen(s1) == ft_strlen(s2)) && (ft_strncmp(s1, s2, ft_strlen(s1)) == 0))
		return (C_TRUE);
	return (C_FALSE);
}

t_bool	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == SPACE)
		return (C_TRUE);
	return (C_FALSE);
}
