NAME := philo

CFLAGS := -Wall -Wextra -Werror -Iinclude #-fsanitize=thread
CC := cc

SRC := src/main.c \
		src/philo.c \
		src/philo_utils.c \
		src/philo_death.c \
		src/parsing.c \
		src/init.c \
		src/utils/ft_atoul.c \
		src/utils/time.c \
		src/exit.c
OBJ := $(SRC:.c=.o)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lpthread -Llib -lft

all:		$(NAME)

clean:
			$(RM) -f $(OBJ)

fclean:		clean
			$(RM) -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

