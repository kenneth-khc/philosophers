/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:10:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/01 06:55:31 by kecheong         ###   ########.fr       */
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

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex	mutex;
	bool	is_picked_up;
	t_mutex	picked_up_mutex;
}	t_fork;

typedef struct s_philosopher
{
	uint64_t		start_time; // milliseconds since Epoch
	t_rules			rules;
	uint16_t		id;
	pthread_t		thread;
	bool			alive;
	uint8_t			state;
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_fork			*left;
	t_fork			*right;
	t_mutex	state_mutex;
	t_mutex	alive_mutex;
	t_mutex	time_mutex;
	t_mutex	eat_count_mutex;
	uint64_t		last_meal_time;
	uint64_t		eat_count;
}	t_philosopher;

typedef struct s_simulation
{
	uint16_t		philo_count;
	t_rules			rules;
	uint64_t		start_time;
	t_philosopher	*philos;
	t_mutex	*forks; // del
	t_fork			*fork_arr;
	
}	t_simulation;


enum e_philo_state
{
	EATING,
	THINKING,
	SLEEPING,
};

typedef enum e_status
{
	SUCCESS,
	E_MALLOC_FAILED,
	E_INVALID_ARG_COUNT,
	E_INVALID_ARG_TYPE,
	E_THREAD_FAILED
} t_status;

t_status init_muts(t_simulation *sim,
	t_philosopher **philos, uint16_t philo_count); // temp
	
t_status	parse_args(int argc, char **argv, t_simulation *args);
t_status	validate_rules(t_simulation *simulation, char **args);
void		handle_errors(t_status status);
t_status	init_philos(t_philosopher **philos, t_simulation *args);
t_status	init_mutexes(t_philosopher **philo, t_mutex **forks,
					int count);
// void		init_hands(t_philosopher **philo, t_mutex **forks, uint16_t count);
void		init_hands(t_philosopher **philo, t_fork *forks, uint16_t count);

// Timing
void		sleep_millisecond(uint64_t milliseconds);
uint64_t	get_current_time(void);
uint64_t	get_time_since(uint64_t start_time);

// Individual philo
void		*philosophize(void *arg);
bool		philo_is_alive(t_philosopher *philo);
// bool		pick_up_fork(t_philosopher *philo, t_mutex *fork);
bool		pick_up_fork(t_philosopher *philo, t_fork *fork);
void		philo_eating(t_philosopher *philo);
void		philo_sleeping(t_philosopher *philo);
void		philo_thinking(t_philosopher *philo);

// Main thread
t_status	start_simulation(t_philosopher *philos, uint16_t philo_count, uint64_t start_time);
void		monitor_philos(t_simulation *sim);
bool		philo_starved(t_philosopher *philo);
bool		check_philos_death(uint16_t philo_count, t_philosopher *philos);
void		kill_philo(t_philosopher *philo);
void		kill_all_philos(uint16_t philo_count, t_philosopher *philos);
bool		check_eat_count(uint16_t philo_count, t_philosopher *philos);

// Utils
void		color_printf(const char *color, uint64_t start_time, uint16_t id,
				const char *message);
void	ft_usleep(uint64_t target_time);
bool	philo_can_eat(t_fork *left_fork, t_fork *right_fork);
#endif