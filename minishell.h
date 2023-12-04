/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:50:58 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/04 11:40:28 by cdupuis          ###   ########.fr       */
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
# include <errno.h>

typedef struct s_fds
{
	char	*name;
	int		fd;
	int		type;
	int		stdin_fd;
	int		stdout_fd;
}	t_fds;

typedef struct s_cmd
{
	int				*pipe;
	char			*cmd;
	char			**args;
	char			*path;
	t_fds			*fds;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	**env;
	t_cmd	*cmd;
	pid_t	pid;
	char	*ret;
	int		err;
}	t_data;

char	**shell_split_tokens(t_data *data, char *line);
int		launch_builtins(t_cmd *cmd, t_data *data, char **tokens);
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
int		shell_env(t_data *data);
int		shell_pwd(t_data *data);
void	sig_exit(int signal, siginfo_t *r_info, void *s);
void	signals_handler(void);
char	*get_env_var(t_data *data, char *token);
char	*get_key_value(char *key);
void	add_cmd_lst(t_cmd **lst, t_cmd *new_cmd);
t_cmd	*lst_new_cmd(void);
void	fill_cmd(char **tokens, t_cmd **cmd);
int		pipe_count(t_data *data, char **tokens);
void	clean_cmd(t_cmd **cmd);
char	**ft_split(char const *s, char c);
int		set_pipes(t_cmd *cmd, t_cmd *c);
void	close_pipes(t_cmd *cmd, t_cmd *skip_cmd);
void	shell_loop(t_data *data);
char	*get_path(t_data *data, t_cmd *cmd);
int		ft_strcmpargs(char *s1, char **s2);
char	*shell_line(t_data *data);
char	*get_lcwd(char *str);
char	*ft_strchr(char c, char *str);
t_cmd	*get_last_cmd(t_cmd *cmd);
void	ft_putendl_fd(char *s, int fd);
char	*replace_env_var(t_data *data, char *token);
int		shell_exit(t_data *data, char **tokens);
char	*ft_strjoin_f(char *s1, char const *s2);
char	*replace_squotes(t_data *data, char *token);
int		check_squotes(char *token, int squotes, int dquotes);
int		heredoc_redirect(t_cmd *last, t_data *data, char **tokens, int i);
t_fds	*new_fds(char *name);
void	fill_heredoc(t_data *data, char *delimiter, int fd);
int		parse_redirect(t_cmd *last, t_data *data, char **tokens, int i);
int		shell_execute(char **tokens, t_data *data);
void	launch_cmd(t_cmd *cmd, t_data *data, char **tokens);
void	malloc_tokens(char *line, char **tokens);
char	**get_tokens(char *line, char **tokens);
char	*erase_quotes(char *token);
char	*search_env_var(t_data	*data, char	*token);
char	*set_ret(char c, char *ret);
void	set_pwd(t_data *data);

#endif