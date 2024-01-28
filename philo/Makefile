NAME = philo
CFLAGS = -Wall -Werror -Wextra
FSAN = -fsanitize=thread -g3
ARGS = 5 1000 100 100 1

SOURCES = main.c parsing.c init.c time.c monitor.c threads.c utils.c

a:
	cc $(SOURCES) $(CFLAGS) $(FSAN) -o $(NAME) && ./$(NAME) $(ARGS)

test:
	cc $(test.c) $(FSAN) -o a.out && ./a.out

all:

clean:

fclean:

re:

.PHONY: all clean fclean re