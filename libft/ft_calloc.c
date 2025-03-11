#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*p;
	size_t			total;

	total = num * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, total);
	return (p);
}
