CC 		= cc
NAME 	= philo_bonus
CFLAGS 	= -Wall -Werror -Wextra
TSAN 	= -fsanitize=thread
# ASAN = -fsanitize=address
DEBUG	= g3
GREEN	= \e[1;32m
RESET	= \e[0m

SOURCES = \
main.c \
parsing.c \
init.c time.c \
philosophize.c \
simulation.c \
philo_monitor.c \
simulation_utils.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -c $(SOURCES)
	@printf "$(GREEN)Built $(NAME).$(RESET)\n"

clean:
	rm -rf $(OBJECTS)
	@printf "$(GREEN)Cleaned object files.$(RESET)\n"
 
fclean: clean
	rm -rf $(NAME)
	@printf "$(GREEN)Cleaned $(NAME).$(RESET)\n"

re: fclean all

# Testing
ARGS = $(PC) $(TTD) $(TTE) $(TTS) $(EC) # Arguments for running philo

PC	= 4 	# Philosopher count
TTD = 410 	# Time for philosopher to die
TTE = 200 	# Time for philosopher to eat
TTS = 200 	# Time for philosopher to sleep
EC 	= 5	 # Eat count. Number of times philosopher should at least eat
log = ../tests/output.log

a:
	$(CC) $(SOURCES) $(CFLAGS) $(TSAN) -o $(NAME)
	./$(NAME) $(ARGS) | tee $(log)

check:
	../tests/check.sh

.PHONY: all clean fclean re