CC = gcc
CFLAGS = -Wall -Wextra -I/Users/cdupuis/.brew/opt/readline/include
NAME = minishell
SRCS = main.c builtins.c tokens_split.c utils.c export.c unset.c libft.c env.c signals.c init_cmd.c
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

fclean :
	rm -f $(OBJS) $(NAME)

.PHONY: all fclean exp linux re
