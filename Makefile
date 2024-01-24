NAME = philo
CFLAGS = -Wall -Werror -Wextra
FSAN = -fsanitize=address -g3
ARGS = 5 100 100 100

SOURCES = philo.c parsing.c time.c eating.c

a:
	cc $(SOURCES) $(CFLAGS) $(FSAN) -o $(NAME) && ./$(NAME) $(ARGS)

test:
	cc $(test.c) $(FSAN) -o a.out && ./a.out

all:

clean:

fclean:

re:

.PHONY: all clean fclean re