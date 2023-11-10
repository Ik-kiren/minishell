/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:50:58 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/10 11:52:27 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_cmd
{
	int				*pipe;
	char			*cmd;
	char			**args;
	char			*path;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	**env;
	t_cmd	*cmd;
	pid_t	pid;
	int		stdin_fd;
}	t_data;

char	**shell_split_tokens(char *line);
int		launch_builtins(int id, char **tokens, t_data *envp);
char	*ft_strjoin(char const *s1, char const *s2);
void	get_allenv(char **envp);
size_t	ft_ptrlen(char **str);
char	*ft_strdup(char *str);
int		ft_strncmp(char *s1, char *s2, int size);
size_t	ft_strlen(const char *str);
void	free_str(char **str);
void	free_ptr(void *ptr);
int		shell_export(char **tokens, t_data *data);
int		shell_unset(char **tokens, t_data *data);
int		get_env_idx(t_data *data, char *token);
int		token_size(char *token);
int		ft_strcmp(char *s1, char *s2);
int		shell_env(t_data *data, char **tokens);
int		shell_pwd(char **tokens, t_data *data);
void	sig_exit(int signal, siginfo_t *r_info, void *s);
void	signals_handler(void);
char	*get_env_var(t_data *data, char *token);
char	*get_key_value(char *key);
void	add_cmd_lst(t_cmd **lst, t_cmd *new_cmd);
t_cmd	*lst_new_cmd();
void	fill_cmd(char **tokens, t_cmd **cmd);
int		pipe_count(t_data *data, char **tokens);
void	clean_cmd(t_cmd **cmd);
char	**ft_split(char const *s, char c);

#endif