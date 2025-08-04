CC		= cc
CFLAGS 	= -Wall -Wextra -Werror -Ilibft -g
SRCS	= main.c utils.c init.c thread_utils.c rotine.c print_utils.c routine_utils.c
OBJS	= $(SRCS:.c=.o)
NAME	= philo


all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o $(NAME) -lpthread

%.o:%.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	make clean -C libft
	rm -f $(OBJS)
	@echo "🧹 Object files removed."

fclean: clean
	make fclean -C libft
	rm -f $(NAME)
	@echo "🗑️ Executable removed//fully cleaned."

re: fclean all

.PHONY: all clean fclean re
