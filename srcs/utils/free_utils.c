#include "minishell.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		if (temp->args)
			ft_free_tab(temp->args);
		free(temp);
	}
}

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->value);
		free(temp);
	}
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->input)
		free(shell->input);
	free_env(shell->env);
	free_cmd(shell->cmd);
	free_tokens(shell->token);
	free(shell);
}
