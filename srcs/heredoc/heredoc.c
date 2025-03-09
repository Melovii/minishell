t_bool is_heredoc(char *input, int *i)
{
	int j;

	j = *i;
	if (input[j + 1] == INPUT_RDRCT)
	{
		if (is_operator(input[j + 2]))
			return (C_FALSE);
		*i = j + 2;
		return (C_TRUE);
	}
	return (C_FALSE);
}

char *find_limiter(t_shell *shell, char *input, int *i)
{
	//
}

static void heredoc_interactive(t_shell *shell, char *input)
{
	int i;
	char *limiter;

	i = -1;
	while (input[++i])
	{
		if (input[i] == INPUT_RDRCT)
		{
			if (is_heredoc(input, &i))
			{

			}
		}
	}

	}
