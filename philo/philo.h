/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:10:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/29 22:49:10 by kecheong         ###   ########.fr       */
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

# include "color.h"

/* Error codes */
typedef enum e_status
{
	SUCCESS,
	E_MALLOC_FAILED,
	E_INVALID_ARG_COUNT,
	E_INVALID_ARG_TYPE,
	E_THREAD_FAILED,
	E_JOIN_FAILED
}	t_status;

/* Rules each philo has to follow. Times are in milliseconds */
typedef struct s_rules
{
	uint64_t	time_to_die;	
	uint64_t	time_to_eat;	
	uint64_t	time_to_sleep;
	bool		eat_limit;
	uint64_t	required_meals;
}	t_rules;

typedef pthread_mutex_t		t_mutex;

typedef struct s_fork
{
	t_mutex	mutex;
}	t_fork;

typedef struct s_simulation	t_simulation;
typedef struct s_philo
{
	t_simulation	*simulation;
	t_rules			*rules;
	t_fork			*left_fork;
	t_fork			*right_fork;
	uint16_t		id;
	pthread_t		thread;
	bool			alive;
	t_mutex			alive_mutex;
	uint64_t		eat_count;
	t_mutex			eat_count_mutex;
	uint64_t		last_meal_time;
	t_mutex			meal_time_mutex;
	uint64_t		death_time;
	t_mutex			death_time_mutex;
}	t_philo;

typedef struct s_simulation
{
	uint16_t	philo_count;
	t_philo		*philos; /* Array of philos */
	t_fork		*forks; /* Array of forks */
	uint64_t	start_time; /* Milliseconds since Epoch */
	t_rules		rules;
	bool		running;
	t_mutex		mutex;
	t_mutex		print_mutex;
}	t_simulation;

/* Argument parsing and initialization */

t_status	parse_args(int argc, char **argv, t_simulation *args);
t_status	init_simulation(t_simulation *simulation);
void		handle_errors(t_status status);

/* Timing */

uint64_t	get_current_time(void);
uint32_t	get_time_since(uint64_t start_time);
void		sleep_ms(uint64_t milliseconds_to_sleep);

/* Philo routines and helper functions for monitoring */

t_status	start_simulation(t_simulation *simulation);
bool		simulation_is_running(t_simulation *simulation);
void		*philosophize(void *arg);
void		*philo_monitor(void	*arg);
bool		philo_is_alive(t_philo *philo);
void		*check_count(void *arg);
bool		philo_starved(t_philo *philo);
t_status	await_philos(t_simulation *simulation);
void		kill_philo(t_philo *philo);
void		kill_philos(t_simulation *simulation);
void		turn_off_simulation(t_simulation *simulation);
void		clean_up(t_simulation *simulation);

/* Logging messages to stdout */

void		log_message(const char *color, t_simulation *simulation,
				const char *msg);
void		log_philo_action(const char *color, t_philo *philo,
				const char *msg);
void		log_philo_death(const char *color, t_simulation *simulation,
				uint16_t id);

#endif