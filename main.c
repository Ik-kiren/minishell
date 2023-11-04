#include "minishell.h"

char *get_lcwd(char *str)
{
    char *tmp;
    int m_len;
    int i;
    int j;

    m_len = ft_strlen(str);
    i = m_len;
    j = 0;
    while (str[i] != '/' && i != 0)
        i--;
    tmp = malloc(sizeof(char) * (m_len - i + 1));
    if (!tmp)
        return NULL;
    while (str[i])
    {
        tmp[j] = str[i];
        j++;
        i++;
    }
    tmp[j] = '\0';
    return tmp;
}

char *get_key_value(char *key)
{
    char *tmp;
    int i;
    int j;

    i = 0;
    j = 0;
    while (key[i] != '=')
    {
        i++;
    }
    tmp = malloc(sizeof(char) * (ft_strlen(key) - i + 1));
    if (!tmp)
        return NULL;
    i++;
    while (key[i])
    {
        tmp[j] = key[i];
        i++;
        j++;
    }
    tmp[j] = '\0';
    return tmp;
}

char *get_prompt(t_data *data, char *cwd)
{
    char *end_cwd;
    char *user;
    char *tmp;
    char *prompt;
    int idx;
    char *tmp_end;

    idx = get_env_idx(data, "USER");
    tmp_end = get_lcwd(cwd);
    end_cwd = ft_strjoin(tmp_end, "$ ");
    tmp = get_key_value(data->env[idx]);
    user = ft_strjoin(tmp, ":");
    prompt = ft_strjoin(user, end_cwd);
    free(end_cwd);
    free(user);
    free(tmp);
    free(tmp_end);
    return prompt;
}

char *shell_line(t_data *data)
{
    char *line;
    char    cwd[4096];
    char *prompt;

    if (!getcwd(cwd, 4096))
        printf("error cwd\n");
    prompt = get_prompt(data, cwd);
    line = NULL;
    line = readline(prompt);
    if (!line)  
        return NULL;
    add_history(line);
    free(prompt);
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
    (void)wpid;
    return 1;
}

int ft_strcmpargs(char *s1, char **s2)
{
    int i;
    int j;
    int found;

    j = 0;
    while (j <= 6)
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

    id = 0;
    if (tokens[0] == NULL)
        return 1;
    printf("id = %d\n", ft_strcmpargs(tokens[0], builtins_str));

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

    while (1)
    {
        line = shell_line(data);
        printf("line = %s\n", line);
        tokens = shell_split_tokens(line);
        status = shell_execute(tokens, data);
        (void)status;
    }
}

void init_data(t_data *data, char **envp)
{
    int len;
    int i;

    i = 0;
    len = ft_ptrlen(envp);
    data->env = malloc(sizeof(char *) * (len + 1));
    while (i < len)
    {
        data->env[i] = ft_strdup(envp[i]);
        i++;
    }
    data->env[i] = NULL;
}

void sig_exit(int signal, siginfo_t *r_info, void *s)
{
    (void)r_info;
    (void)s;
    (void)signal;

    write(1, "\n", 1);
    rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_data data;
    struct sigaction response;

    response.sa_sigaction = sig_exit;
    sigemptyset(&response.sa_mask);
    response.sa_flags = 0;
    sigaction(SIGINT, &response, NULL);
    init_data(&data, envp);
    shell_loop(&data);
}