NAME = philo
CFLAGS = -Wall -Werror -Wextra
# FSAN = -fsanitize=thread -g3
# # FSAN = -fsanitize=address -g3
ARGS = 10 300 100 100 10

SOURCES = main.c parsing.c init.c time.c monitor.c philosophize.c utils.c validating.c

a:
	cc $(SOURCES) $(CFLAGS) $(FSAN) -o $(NAME)
	./$(NAME) $(ARGS) > output.log && cat output.log

test:
	cc $(test.c) $(FSAN) -o a.out && ./a.out

all:

clean:

fclean:

re:

.PHONY: all clean fclean re