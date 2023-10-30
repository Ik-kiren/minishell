#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

char **shell_split_tokens(char *line);
int launch_builtins(int id, char **tokens, char **envp);
char **ft_ptrjoin(char *s1, char **s2);
void get_allenv(char **envp);
int ft_ptrlen(char **str);

#endif