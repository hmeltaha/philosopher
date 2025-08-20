CC		= cc
CFLAGS 	= -Wall -Wextra -Werror
SRCS	= main.c utils.c init.c thread_utils.c routine.c print_utils.c routine_utils.c libft_utils.c eat_utils.c monitor.c
OBJS	= $(SRCS:.c=.o)
NAME	= philo


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

%.o:%.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
	@echo "🧹 Object files removed."

fclean: clean
	rm -f $(NAME)
	@echo "🗑️ Executable removed//fully cleaned."

re: fclean all

.PHONY: all clean fclean re
