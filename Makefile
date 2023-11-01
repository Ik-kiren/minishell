CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
SRCS = main.c builtins.c tokens_split.c utils.c
OBJS = $(SRCS:c=o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

re : fclean all	

fclean :
	rm -f $(OBJS) $(NAME)

.PHONY: all fclean re
