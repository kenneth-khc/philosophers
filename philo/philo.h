/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:10:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/29 17:22:27 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

/* Ansi color codes */
# define BLACK "\e[0;30m"
# define MAGENTA "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define RED "\e[0;35m"
# define BOLD_RED "\e[1;31m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define COLOR_RESET "\e[0m"

// #define BLACK ""
// #define MAGENTA ""
// #define GREEN ""
// #define YELLOW ""
// #define BLUE ""
// #define RED ""
// #define BOLD_RED ""
// #define CYAN ""
// #define WHITE ""
// #define COLOR_RESET ""

typedef struct s_rules
{
	uint16_t	philo_count;
	uint64_t	time_to_die;	// milliseconds
	uint64_t	time_to_eat;	// milliseconds
	uint64_t	time_to_sleep;	// milliseconds
	int64_t		min_eat;
}	t_rules;

typedef struct s_philosopher
{
	uint64_t		start_time; // milliseconds since Epoch
	t_rules			rules;
	uint16_t		id;
	pthread_t		thread;
	bool			alive;
	uint8_t			state;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	alive_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	eat_count_mutex;
	uint64_t		last_meal_time;
	uint64_t		eat_count;
}	t_philosopher;

typedef struct s_simulation
{
	uint16_t		philo_count;
	t_rules			rules;
	uint64_t		start_time;
	t_philosopher	*philos;
	pthread_mutex_t	*forks;
}	t_simulation;

enum
{
	EATING,
	THINKING,
	SLEEPING,
	DEAD
};

enum e_status
{
	SUCCESS,
	E_MALLOC_FAILED,
	E_INVALID_ARG_COUNT,
	E_INVALID_ARG_TYPE
};

enum e_status		parse_args(int argc, char **argv, t_simulation *args);
enum e_status	validate_rules(t_rules *rules, char **args);
void	handle_error(enum e_status status);
bool	invalid_args(t_rules *rules, char **args);
enum e_status	init_philos(t_philosopher **philos, t_simulation *args);
bool		init_mutexes(t_philosopher **philo, pthread_mutex_t **forks,
				int count);
// void		init_hands(t_philosopher *philo, t_simulation *sim);
void		init_hands(t_philosopher **philo, pthread_mutex_t **forks, uint16_t count);

// Timing
void		sleep_millisecond(uint64_t milliseconds);
uint64_t	get_current_time(void);
uint64_t	get_time_since(uint64_t start_time);

// Individual philo
void		*philosophize(void *arg);
bool		philo_is_alive(t_philosopher *philo);
bool		pick_up_left_fork(t_philosopher *philo);
bool		pick_up_right_fork(t_philosopher *philo);
void		philo_eating(t_philosopher *philo);
void		philo_sleeping(t_philosopher *philo);
void		philo_thinking(t_philosopher *philo);

// Main thread
void	start_simulation(t_philosopher *philos, uint16_t philo_count, uint64_t start_time);
void		monitor_philos(t_simulation *sim);
bool		philo_starved(t_philosopher *philo);
bool		check_philos_death(uint16_t philo_count, t_philosopher *philos);
void		kill_philo(t_philosopher *philo);
void		kill_all_philos(uint16_t philo_count, t_philosopher *philos);
bool		check_eat_count(uint16_t philo_count, t_philosopher *philos);

// Utils
void		color_printf(const char *color, uint64_t start_time, uint16_t id,
				const char *message);
bool	invalid_arg(char *original, char *reconverted);

#endif