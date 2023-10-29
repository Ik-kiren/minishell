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

int shell_launch(char **tokens, char **envp)
{
    pid_t pid;
    pid_t wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execve(tokens[0], tokens, envp) == -1)
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

int ft_strcmp(char *s1, char **s2)
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

int shell_cd(char **tokens)
{
    if (tokens[1] == NULL)
        fprintf(stderr, "pathname error");
    else
        if (chdir(tokens[1]) != 0)
          perror("lsh3"); 
    return 1;
}

int shell_echo(char **tokens)
{
    int i;

    i = 1;
    while (tokens[i])
    {
        printf("%s ", tokens[i]);
        i++;
    }
    printf("\n");
    return 1;
}

int shell_pwd()
{
    char *pwd;

    pwd = getenv("PWD");
    printf("%s\n", pwd);
    return 1;
}

int launch_builtins(int id, char **tokens)
{
    int ret;

    if (id == 1)
        ret = shell_cd(tokens);
    else if (id == 2)
        ret = shell_echo(tokens);
    else if(id == 3)
        ret = shell_pwd();
    return ret;
}

int shell_execute(char **tokens, char **envp)
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
    if ((id = ft_strcmp(tokens[0], builtins_str)))
    {
        return (launch_builtins(id, tokens));
    }
    return (shell_launch(tokens, envp));
}

void shell_loop(char **envp)
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
        status = shell_execute(tokens, envp);
    }
}

int main(int argc, char **argv, char **envp)
{
    shell_loop(envp);
}