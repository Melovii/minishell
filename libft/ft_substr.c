#include "libft.h"

static char	*ft_zero_exception_handle(void)
{
	char	*arr;

	arr = malloc(1);
	if (!arr)
		return (NULL);
	arr[0] = '\0';
	return (arr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*arr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		arr = ft_zero_exception_handle();
		return (arr);
	}
	if (start + len > ft_strlen(s))
		arr = malloc(ft_strlen(s) - start + 1);
	else
		arr = malloc(len + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
