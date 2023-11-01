#include "minishell.h"

char *shell_line()
{
    char *line;

    line = NULL;
    line = readline(NULL);
        if (!line)  
            return NULL;
    return line;
}

int shell_launch(char **tokens, t_data *data)
{
    pid_t pid;
    pid_t wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execve(tokens[0], tokens, data->env) == -1)
            perror("lsh1");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
        perror("lsh2");
    else
    {
        while(!WIFEXITED(status) && !WIFSIGNALED(status))
            wpid = waitpid(pid, &status, WUNTRACED);
    }
    return 1;
}

int ft_strcmpargs(char *s1, char **s2)
{
    int i;
    int j;
    int found;

    j = 0;
    while (j < 6)
    {
        i =0 ;
        found = 1;
        while (s1[i])
        {
            if (s1[i] != s2[j][i])
            {
                found = 0;
                break ;
            }
            i++;
        }
        if (found == 1)
        {
            return (j + 1);
        }
        j++;
    }
    return 0;
}

int shell_execute(char **tokens, t_data *data)
{
    int i;
    int id;
    char *builtins_str[] = {
        "cd",
        "echo",
        "pwd",
        "export",
        "unset",
        "env",
        "exit"
    };

    i = 0;
    id = 0;
    if (tokens[0] == NULL)
        return 1;
    if ((id = ft_strcmpargs(tokens[0], builtins_str)))
    {
        return (launch_builtins(id, tokens, data));
    }
    return (/*shell_launch(tokens, envp)*/0);
}

void shell_loop(t_data *data)
{
    char    *line;
    char    **tokens;
    int     status;
    char    cwd[4096];

    while (1)
    {
        if (!getcwd(cwd, 4096))
            printf("error cwd\n");
        else
            printf("%s : ", cwd);
        line = shell_line();
        printf("line = %s\n", line);
        tokens = shell_split_tokens(line);
        status = shell_execute(tokens, data);
    }
}

void init_data(t_data *data, char **envp)
{
    int len;
    int i;

    i = 0;
    len = ft_ptrlen(envp);
    data->env = malloc(sizeof(char *) * len);
    while (i < len)
    {
        data->env[i] = ft_strdup(envp[i]);
        i++;
    }
    data->env[i] = NULL;
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_data data;

    init_data(&data, envp);
    shell_loop(&data);
}