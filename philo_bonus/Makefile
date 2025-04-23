NAME = philo_bonus

CC = cc

FLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=thread

SRCS = actions.c check_argv.c errors.c forks.c free_philo.c init_philos.c philosophers.c s_entries.c task.c time.c utils.c

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re