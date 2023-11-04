#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_data
{
	char	**env;
}	t_data;

char	**shell_split_tokens(char *line);
int		launch_builtins(int id, char **tokens, t_data *envp);
char	*ft_strjoin(char const *s1, char const *s2);
void	get_allenv(char **envp);
size_t	ft_ptrlen(char **str);
char	*ft_strdup(char *str);
int		ft_strncmp(char *s1, char *s2, int size);
size_t	ft_strlen(const char *str);
void	free_str(char *str);
int		free_ptr(char **ptr);
int		shell_export(char **tokens, t_data *data);
int		shell_unset(char **tokens, t_data *data);
int		get_env_idx(t_data *data, char *token);
int		token_size(char *token);

#endif