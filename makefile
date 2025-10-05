CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
SRCDIR  = src
SRCS    = $(SRCDIR)/main.c $(SRCDIR)/utils.c $(SRCDIR)/init.c $(SRCDIR)/thread_utils.c \
          $(SRCDIR)/routine.c $(SRCDIR)/print_utils.c $(SRCDIR)/routine_utils.c \
          $(SRCDIR)/libft_utils.c $(SRCDIR)/eat_utils.c $(SRCDIR)/monitor.c
OBJS    = $(SRCS:.c=.o)
NAME    = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

$(SRCDIR)/%.o: $(SRCDIR)/%.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@echo "🧹 Object files removed."

fclean: clean
	rm -f $(NAME)
	@echo "🗑️ Executable removed//fully cleaned."

re: fclean all

.PHONY: all clean fclean re
