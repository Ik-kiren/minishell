/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:50:58 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/19 12:29:49 by cdupuis          ###   ########.fr       */
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
# include <sys/stat.h>

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
	t_fds			*fdh;
	int				err;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char				**env;
	t_cmd				*cmd;
	pid_t				pid;
	int					ret;
	int					err;
	int					doc;
	int					i;
	int					arg;
	int					status;
}	t_data;

char	**shell_split_tokens(t_data *data, char *line);
int		launch_builtins(t_cmd *cmd, t_data *data, char **tokens);
char	*ft_strjoin(char const *s1, char const *s2);
void	get_allenv(char **envp, char *str);
size_t	ft_ptrlen(char **str);
char	*ft_strdup(char *str);
int		ft_strncmp(char *s1, char *s2, int size);
size_t	ft_strlen(const char *str);
void	free_str(char **str);
void	*free_ptr(void *ptr);
int		shell_export(char **tokens, t_data *data);
int		shell_unset(char **tokens, t_data *data);
int		get_env_idx(t_data *data, char *token);
int		token_size(char *token);
int		ft_strcmp(char *s1, char *s2);
int		shell_env(t_data *data);
int		shell_pwd(t_data *data);
void	sig_exit(int signal, siginfo_t *r_info, void *s);
void	signals_handler(void);
char	*get_env_var(t_data *data, char *token, int *dolars);
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
int		check_squotes(char *token);
int		heredoc_redirect(t_cmd *last, t_data *data, char **tokens, int i);
t_fds	*new_fds(char *name);
void	fill_heredoc(t_data *data, char *delimiter, int fd);
int		parse_redirect(t_cmd *last, t_data *data, char **tokens, int *i);
int		shell_execute(char **tokens, t_data *data);
void	launch_cmd(t_cmd *cmd, t_data *data, char **tokens);
void	malloc_tokens(char *line, char **tokens);
char	**get_tokens(char *line, char **tokens);
char	*erase_quotes(char *token, int quotes);
char	*search_env_var(t_data	*data, char	*token);
char	*set_ret(char c, char *ret);
void	set_pwd(t_data *data);
int		quotes_states(char *token, int i, int *quotes);
int		check_op_quotes(char *token);
int		print_error(char *str);
int		ft_atoi(const char *str);
int		check_number(char *str);
int		quotes_states2(char *token, int i, int *quotes, int *dquotes);
int		check_utils(char c);
int		set_env_variable(t_data *data, char *token);
int		check_spchar(char c);
int		check_export(char *str);
int		count_quotes(char *line, int i, int count);
void	double_free(void *ptr1, void *ptr2);
void	get_sort_exp(char **envp);
char	*ft_itoa(int n);
void	set_signals_noninteractive(void);
int		c_pr(char c);
int		parse_env_var(t_data *data, char **tokens);
char	*erase_env_var(char *token);
int		check_line(char *line);
void	set_signals_noninteractive(void);
int		ft_atol(char **str, int *fail);
int		ft_isdigit(int c);
int		ft_isnumber(char *str);
int		ft_strncmp2(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_f2(char *s1, char *s2);
int		check_sp(char c);
int		_echo(t_cmd *cmd);
char	*max(char *s1, char *s2);
void	unlink_doc(t_cmd *last);
int		shell_echo(t_data *data, char **tokens);
char	**ft_realloc(char **tab1, char *s1);
void	check_args(t_cmd *tmp, char **tokens, int *i);
void	fill_ic_utils(t_cmd *tmp, char **tokens, int *i);
void	get_t_u(int *q, int *dq);
void	cd_path(t_data *data);
int		unset_env_variable(t_data *data, char *token);
char	*ft_strjoin_f1(char const *s1, char *s2);
void	shlevel(t_data *data);
int		check_cmd(t_data *data, t_cmd *cmd);

#endif