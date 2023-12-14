CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/Users/cdupuis/.brew/opt/readline/include -g -fsanitize=address
NAME = minishell
SRCS = main.c builtins.c tokens_split.c utils.c export.c unset.c libft.c env.c signals.c init_cmd.c ft_split.c pipes.c shell.c path.c line.c parse_quotes.c free_utils.c heredoc.c redirections.c execute.c cmd_utils.c utils2.c quotes.c get_tokens.c malloc_tokens.c replace_env_var.c utils3.c export_sort.c itoa.c utils4.c env_utils.c search_env_var.c check_line.c
OBJS = $(SRCS:c=o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L/Users/cdupuis/.brew/opt/readline/lib -lreadline -o $(NAME)

linux : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

exp:
	export LDFLAGS="-L/Users/cdupuis/.brew/opt/readline/lib"
	export CPPFLAGS="-I/Users/cdupuis/.brew/opt/readline/include"

re : fclean all	

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

.PHONY: all clean fclean exp linux re
