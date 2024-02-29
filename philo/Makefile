CC 		= cc
NAME 	= philo
CFLAGS 	= -Wall -Werror -Wextra $(TSAN) $(ASAN) $(DEBUG)
# TSAN 	= -fsanitize=thread
# ASAN 	= -fsanitize=address
DEBUG	= -g3
GREEN	= \e[1;32m
RESET	= \e[0m

SOURCES = main.c parsing.c init.c time.c philosophize.c simulation.c philo_monitor.c simulation_utils.c waiter.c
OBJ_DIR = objects/
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
OBJECTS := $(addprefix $(OBJ_DIR), $(OBJECTS))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@printf "$(GREEN)Built $(NAME).$(RESET)\n"

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
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