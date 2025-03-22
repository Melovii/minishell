#include "minishell.h"

static void close_unused_pipes(int **pipe_fd, int num_pipes, int i, int is_child)
{
    if (is_child)
    {
        // In child: Close unused pipe ends (Read/Write ends)
        if (i > 0)   // Close the read end of the previous pipe
            close(pipe_fd[i - 1][0]);
        if (i < num_pipes)  // Close the write end of the current pipe
            close(pipe_fd[i][1]);
    }
    else
    {
        // In parent: Close both ends of all pipes after fork
        for (int j = 0; j < num_pipes; j++)
        {
            close(pipe_fd[j][0]);
            close(pipe_fd[j][1]);
        }
    }
}

static void child_prc(t_cmd *cmd, int **pipe_fd, int num_pipes, int i)
{
    // Set up the file descriptors for pipes
    if (cmd->in_fd != STDIN_FILENO)
        dup2(cmd->in_fd, STDIN_FILENO);
    if (cmd->out_fd != STDOUT_FILENO)
        dup2(cmd->out_fd, STDOUT_FILENO);

    // Close unused pipe ends in the child process
    close_unused_pipes(pipe_fd, num_pipes, i, 1);

    // Execute the command
    if (execvp(cmd->args[0], cmd->args) == -1)
    {
        perror("Execvp failed");
        exit(EX_KO);  // Ensure the child exits if execvp fails
    }
}

static void parent_prc(pid_t pid)
{
    int status;

    // Wait for the child process to finish
    if (waitpid(pid, &status, 0) == -1)
        handle_error("Error waiting for child", EX_KO);

    // Handle child exit status
    if (WIFEXITED(status))
        printf("Child exited with status %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("Child process terminated by signal %d\n", WTERMSIG(status));
}

int exec_cmd(t_shell *shell, t_cmd *cmd)
{
    pid_t pid;
    int num_pipes;
    int **pipe_fd;
    int i = 0;

    num_pipes = count_pipes(cmd);
    pipe_fd = handle_pipe(shell, cmd, num_pipes);

    while (cmd)
    {
		printf("Forking process %d for command: %s\n", i, cmd->args[0]);
        pid = fork();
        if (pid < 0)
        {
            handle_error("Error forking", EX_KO);
        }
        else if (pid == 0)  // Child process
        {
            child_prc(cmd, pipe_fd, num_pipes, i);
        }
        else  // Parent process
        {
            parent_prc(pid);  // Wait for the child to finish
        }

        // Move to the next command after forking
        cmd = cmd->next;
        i++;
    }

    // Close all pipes in the parent process after forking all children
    close_unused_pipes(pipe_fd, num_pipes, i, 0);

    return (1);  // Return a success status
}
