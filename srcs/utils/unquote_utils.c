#include "minishell.h"

static  void init_vars(int *i, int *j, bool *in_sq, bool *in_dq);
static int measure_unquoted_length(char *str);
static void copy_unquoted_content(char *dst, char *src);

// * Removes quotes from a string and returns a new string without them
char *remove_quotes_update_str(t_shell *shell, char *str)
{
    char *new_str;
    int len;

    if (!str)
    {
        return (NULL);
    }
    len = measure_unquoted_length(str);
    new_str = ft_calloc(len + 1, sizeof(char));
    if (!new_str)
    {
        shut_program(shell, true, EX_KO);
    }
    copy_unquoted_content(new_str, str);
    free(str);
    return (new_str);
}

// * Initializes variables used for quote detection and indexing
static void  init_vars(int *i, int *j, bool *in_sq, bool *in_dq)
{
    *i = 0;
    *j = 0;
    *in_sq = false;
    *in_dq = false;
}

// * Measures the length of the string excluding quotes (single and double)
static int measure_unquoted_length(char *str)
{
    bool in_sq;
    bool in_dq;
    int i;
    int len;

    init_vars(&i, &len, &in_sq, &in_dq);
    while (str[i])
    {
        if (!in_sq && !in_dq && str[i] == '\'')
            in_sq = 1;
        else if (in_sq && str[i] == '\'')
            in_sq = 0;
        else if (!in_sq && !in_dq && str[i] == '"')
            in_dq = 1;
        else if (in_dq && str[i] == '"')
            in_dq = 0;
        else
            len++;
        i++;
    }
    return len;
}

// * Copies the content of the string excluding quotes (single and double)
static void copy_unquoted_content(char *dst, char *src)
{
    bool in_sq;
    bool in_dq;
    int i;
    int j;

    init_vars(&i, &j, &in_sq, &in_dq);
    while (src[i])
    {
        if (!in_sq && !in_dq && src[i] == '\'')
            in_sq = 1;
        else if (in_sq && src[i] == '\'')
            in_sq = 0;
        else if (!in_sq && !in_dq && src[i] == '"')
            in_dq = 1;
        else if (in_dq && src[i] == '"')
            in_dq = 0;
        else
            dst[j++] = src[i];
        i++;
    }
    dst[j] = '\0';
}
