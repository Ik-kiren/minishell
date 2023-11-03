CC = gcc
CFLAGS = -Wall -Wextra
NAME = minishell
SRCS = main.c builtins.c tokens_split.c utils.c export.c unset.c
OBJS = $(SRCS:c=o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

re : fclean all	

fclean :
	rm -f $(OBJS) $(NAME)

.PHONY: all fclean re
