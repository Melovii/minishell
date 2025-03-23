#include "minishell.h"

// * Function to print the current working directory
int	ft_pwd()
{
	size_t	size;
	char	*buf;

	size = 256;
	// Get CWD buffer with getcwd and malloc buffer size of 256 bytes (size)
	while (!(buf = getcwd(malloc(size), size))) // Try getting CWD, expand buffer if needed
	{
		free(buf); 
		if (size > 4096) // Prevent infinite loop
			handle_error("getcwd: path too long", EX_KO);
		size *= 2;
    }

	// Print CWD buffer
	printf("%s\n", buf);
	free(buf);
	return (EX_OK);
}
