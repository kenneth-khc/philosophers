/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:10:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/28 22:23:03 by kecheong         ###   ########.fr       */
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


#include <errno.h>
#include <string.h>
#include "color.h"

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

typedef struct s_philo t_philo;
typedef struct s_simulation	t_simulation;
typedef struct s_philo
{
	t_simulation	*simulation;
	t_rules			*rules;
	uint16_t		id;
	pthread_t		thread;
	bool			alive;
	uint64_t		eat_count;
	uint64_t		last_meal_time;
	uint64_t		death_time;
	sem_t			*forks; /* Pointer to all the forks on the table */
	sem_t			*mealtime_semaphore; /* Semaphore as mutex to protect philo's death time */
	struct timeval	mealtime;
}	t_philo;

typedef struct s_simulation
{
	uint16_t	philo_count;
	t_philo		philo;	/* Philo structure used to hold each philo and then cloned */
	uint64_t	start_time; /* Milliseconds since Epoch */
	t_rules		rules;
	sem_t		*forks;	/* Available forks on the table represented by a semaphore */
	bool		running;
	sem_t		*printer;
	pid_t		*pids; /* Array of process IDs that refer to each philo */
	sem_t		*eat_counter; /* Signal eat counter everytime a philo hits their target */
	sem_t		**mealtime_semaphores; /* Array of semaphores for each philo */
	int			dead_ret;
	pthread_mutex_t	lock;
}	t_simulation;
#include <stdarg.h>

#define log(fmt, ...) \
fprintf(stdout, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__);

/* Argument parsing and initialization */

void		parse_args(int argc, char **argv, t_simulation *args);
// void		init_simulation(t_simulation *simulation);
void init_semaphores(t_simulation *sim);

/* Timing */

uint64_t	get_current_time(void);
uint32_t	get_time_since(uint64_t start_time);
void		sleep_ms(uint64_t milliseconds_to_sleep);

/* Philo routines and helper functions for monitoring */

void		start_simulation(t_simulation *simulation);
void		*philosophize(void *arg);
void		*philo_monitor(void	*arg);
bool		philo_is_alive(t_philo *philo);
void		*check_count(void *arg);
bool		philo_starved(t_philo *philo);
void		await_philos(t_simulation *simulation);
void		kill_philo(t_philo *philo);
void		kill_philos(t_simulation *simulation);
void		clean_up(t_simulation *simulation);
void	fork_philos(t_simulation *sim);

/* Logging messages to stdout */

void		log_message(const char *color, t_simulation *simulation,
				const char *msg);
void		log_philo_action(const char *color, t_philo *philo,
				const char *msg);
void		log_philo_death(const char *color, t_simulation *simulation,
				uint16_t id);
void	error_and_exit(t_status	errcode);

# if 1
#include <signal.h>
void	set_sigterm_handler(void);
void	flush_output(int signum);
# endif
#endif