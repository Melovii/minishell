#include "minishell.h"
#include "../libft/libft.h"

static void	eof_msg(t_shell *shell, char *delimiter);
static int setup_heredoc(t_shell *shell, t_dir *redir);
static void handle_heredoc_child(t_shell *shell, t_dir *redir);
static int wait_for_heredoc_child(pid_t pid);

int process_heredocs(t_shell *shell)
{
    t_cmd   *cmd;
    t_dir   *redir;
    int     result;

    cmd = shell->cmd;
    while (cmd)
    {
        redir = cmd->redir_list;
        while (redir)
        {
            if (redir->type == DIR_HEREDOC)
            {
                result = setup_heredoc(shell, redir);
                if (result != EX_OK)
                    return (result); // error or interrupt
            }
            redir = redir->next;
        }
        cmd = cmd->next;
    }
    return (EX_OK);
}

static int setup_heredoc(t_shell *shell, t_dir *redir)
{
    pid_t pid;

    if (pipe(redir->heredoc_fd) == -1)
    {
        shut_program(shell, true, EXIT_FAILURE);
        return (HEREDOC_PIPE_ERROR); // * Cannot be reached
    }
    pid = fork();
    if (pid < 0)
    {
        shut_program(shell, true, HEREDOC_FORK_ERROR);
        return (HEREDOC_FORK_ERROR); // * Cannot be reached
    }
    else if (pid == 0)
        handle_heredoc_child(shell, redir);
    close(redir->heredoc_fd[1]);
    return (wait_for_heredoc_child(pid)); // exit code or (128+sig)
}

static void handle_heredoc_child(t_shell *shell, t_dir *redir)
{
    char    *line;

    // TODO: Handle signals (Ctrl+C, Ctrl+D, Ctrl+\)

    while (1)
    {
        line = readline(HEREDOC_PROMPT);
        if (!line)
            break;
        if (are_strs_equal(line, redir->filename))
        {
            free(line);
            break;
        }
        ft_putendl_fd(line, redir->heredoc_fd[1]);
        free(line);
    }
    close(redir->heredoc_fd[1]);
    if (!line)
    {
        eof_msg(NULL, redir->filename);
    }
    shut_program(shell, false, EX_OK);    // Delimiter matched, also Ctrl+D treated as success
}

static int wait_for_heredoc_child(pid_t pid)
{
    int status;
    int signal_num;
    int exit_code;

    exit_code = 1;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        exit_code = WEXITSTATUS(status);
        return (exit_code);
    }
    else if (WIFSIGNALED(status))
    {
        signal_num = WTERMSIG(status);
        return (128 + signal_num);
    }
    return (exit_code); // Undefined behavior, should not happen!
}

static void	eof_msg(t_shell *shell, char *delimiter)
{
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putnbr_fd((int)shell->number_of_prompts, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}


