CC = cc
NAME = philo_bonus
CFLAGS = -Wall -Werror -Wextra -g3
FSAN = -fsanitize=thread -g3
# FSAN = -fsanitize=address -g3

ARGS = $(PC) $(TTD) $(TTE) $(TTS) $(EC)
PC = 4 # Philosopher count
TTD = 410 # Time for philosopher to die
TTE = 200 # Time for philosopher to eat
TTS = 200 # Time for philosopher to sleep
EC = 5	 # Eat count. Number of times philosopher should at least eat
log = ../tests/output.log

SOURCES = \
main.c \
parsing.c \
init.c time.c \
philosophize.c \
simulation.c \
philo_monitor.c \
simulation_utils.c \

a:
	$(CC) $(SOURCES) $(CFLAGS) $(FSAN) -o $(NAME)
	./$(NAME) $(ARGS) | tee $(log)

check:
	../tests/check.sh

test:
	cc $(test.c) $(FSAN) -o a.out && ./a.out

all:

clean:

fclean:

re:

.PHONY: all clean fclean re