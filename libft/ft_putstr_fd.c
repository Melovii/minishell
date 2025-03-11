#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s)
		return ;
	if (s)
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
}
