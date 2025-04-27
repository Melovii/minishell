#include "../libft/libft.h"

char	*ft_strjoin_path(char *dir, char *cmd)
{
	char	*joined;
	char	*temp;

	if (!dir || !cmd)
		return (NULL);
	if (dir[ft_strlen(dir) - 1] == '/')
		return (ft_strjoin(dir, cmd));
	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	joined = ft_strjoin(temp, cmd);
	free(temp);
	return (joined);
}
