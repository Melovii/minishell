#include "minishell.h"
#include <string.h> // ! REPLACE STRCMP ;-;

// TODO: Split parse_input into two functions
// TODO: Fix norm, and add comments for some parts
// TODO: Replace STRCMP with FT function

// * Function to add a token value to the args array of the current command
void add_to_cmd_args(t_cmd *cmd, char *value)
{
    if (!cmd || !value)
        return;

    if (!cmd->args)
    {
        cmd->args = malloc(sizeof(char *) * 2);
        if (!cmd->args)
        {
            perror("malloc failed");
            return;
        }
        cmd->args[0] = ft_strdup(value);
        cmd->args[1] = NULL;
        return;
    }

    int len = 0;
    while (cmd->args[len])
        len++;

    cmd->args = realloc(cmd->args, sizeof(char *) * (len + 2));
    if (!cmd->args)
    {
        perror("realloc failed");
        return;
    }

    cmd->args[len] = ft_strdup(value);
    cmd->args[len + 1] = NULL;
}


// * Function to parse the tokens and build a list of commands
// ? (btw why not just use ft_calloc?)
t_cmd *parse_input(char *input)
{
    t_token *tokens;
    t_cmd *cmd = NULL;
    t_cmd *current_cmd = NULL;

    tokens = tokenizer(input);
    if (!tokens)
        return NULL;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    current_cmd = cmd;
    current_cmd->args = NULL;
    current_cmd->in_fd = -1;
    current_cmd->out_fd = -1;
    current_cmd->next = NULL;

    while (tokens)
    {
        if (tokens->value && strcmp(tokens->value, "|") == 0)
        {
            current_cmd->next = malloc(sizeof(t_cmd));
            if (!current_cmd->next)
                return NULL;
            current_cmd = current_cmd->next;
            current_cmd->args = NULL;
            current_cmd->in_fd = -1;
            current_cmd->out_fd = -1;
            current_cmd->next = NULL;
        }
        else
        {
            add_to_cmd_args(current_cmd, tokens->value);
        }

        tokens = tokens->next;
    }

    return (cmd);
}


// * Function to build an AST from the token list
t_cmd *build_ast(t_token *tokens)
{
    t_cmd *cmd = NULL;
    t_cmd *current_cmd = NULL;

    while (tokens)
    {
        if (strcmp(tokens->value, "|") == 0)
        {
            current_cmd->next = malloc(sizeof(t_cmd));
            current_cmd = current_cmd->next;
            current_cmd->args = NULL;
            current_cmd->in_fd = -1;
            current_cmd->out_fd = -1;
        }
        else
        {
            add_to_cmd_args(current_cmd, tokens->value);
        }

        tokens = tokens->next;
    }

    return (cmd);
}

// * Function to check if the syntax of the tokens is valid
int syntax_checker(char **tokens)
{
    int i = 0;

    while (tokens[i])
    {
        if ((strcmp(tokens[i], "|") == 0 && (i == 0 || !tokens[i + 1] || strcmp(tokens[i + 1], "|") == 0)))
        {
            return (0);
        }
        if ((strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], ">") == 0) && (i == 0 || !tokens[i + 1]))
        {
            return (0);
        }
        i++;
    }

    return (1);
}

// * Function to print the tokens
void print_cmd_list(t_cmd *cmd)
{
    if (!cmd)
    {
        printf("No commands to print.\n");
        return;
    }

    while (cmd)
    {
        printf("Command:\n");

        if (cmd->args)
        {
            int i = 0;
            while (cmd->args[i])
            {
                printf("  Arg %d: %s\n", i + 1, cmd->args[i]);
                i++;
            }
        }
        else
        {
            printf("  No arguments.\n");
        }
        if (cmd->next)
        {
            printf("  (next command)\n");
        }

        cmd = cmd->next;
    }
}
