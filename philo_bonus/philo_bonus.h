/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:10:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/29 22:39:25 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include "color.h"

# if 0
#  include <signal.h>

void		set_sigterm_handler(void);
void		flush_output(int signum);

# endif

/* Error codes */
typedef enum e_status
{
	SUCCESS,
	E_MALLOC_FAILED,
	E_INVALID_ARG_COUNT,
	E_INVALID_ARG_TYPE,
	E_THREAD_FAILED,
	E_JOIN_FAILED,
	E_FORK_FAILED
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

typedef struct s_philo		t_philo;
typedef struct s_simulation	t_simulation;
typedef struct s_philo
{
	t_simulation	*simulation;
	t_rules			*rules;
	uint16_t		id;
	pthread_t		monitor;
	bool			alive;
	uint64_t		eat_count;
	sem_t			*forks; /* Pointer to all the forks on the table */
	sem_t			*mealtime_semaphore; /* Semaphore as mutex */
	struct timeval	mealtime;
}	t_philo;

typedef struct s_simulation
{
	t_rules		rules;
	uint16_t	philo_count;
	t_philo		philo; /* Philo info to be cloned */
	pid_t		*pids; /* Array of PIDs that refer to each philo */
	uint64_t	start_time; /* Milliseconds since Epoch */
	sem_t		*forks; /* Available forks represented by a semaphore */
	sem_t		*printer;
	sem_t		*eat_counter; /* Signalled when a philo is full */
	sem_t		**mealtime_semaphores; /* Array of semaphores for each philo */
}	t_simulation;

/* Argument parsing and initialization */

void		parse_args(int argc, char **argv, t_simulation *args);
void		init_semaphores(t_simulation *sim);

/* Timing */

uint64_t	get_current_time(void);
uint32_t	get_time_since(uint64_t start_time);
void		sleep_ms(uint64_t milliseconds_to_sleep);

/* Philo routines and helper functions for monitoring */

void		start_simulation(t_simulation *simulation);
void		*philosophize(void *arg);
void		*philo_monitor(void	*arg);
void		*check_count(void *arg);
bool		philo_starved(t_philo *philo);
void		await_philos(t_simulation *simulation);
void		clean_up(t_simulation *simulation);

/* Logging messages to stdout */

void		log_message(const char *color, t_simulation *simulation,
				const char *msg);
void		log_philo_action(const char *color, t_philo *philo,
				const char *msg);
void		log_philo_death(const char *color, t_simulation *simulation,
				uint16_t id);
void		error_and_exit(t_status	errcode);

#endif