/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:10:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/07 23:33:46 by kecheong         ###   ########.fr       */
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
// # define BLACK "\e[0;30m"
// # define MAGENTA "\e[0;31m"
// # define GREEN "\e[0;32m"
// # define YELLOW "\e[0;33m"
// # define BLUE "\e[0;34m"
// # define RED "\e[0;35m"
// # define BOLD_RED "\e[1;31m"
// # define CYAN "\e[0;36m"
// # define WHITE "\e[0;37m"
// # define COLOR_RESET "\e[0m"

# define BLACK ""
# define MAGENTA ""
# define GREEN ""
# define YELLOW ""
# define BLUE ""
# define RED ""
# define BOLD_RED ""
# define CYAN ""
# define WHITE ""
# define COLOR_RESET ""

typedef struct s_rules
{
	uint64_t	time_to_die;	// milliseconds
	uint64_t	time_to_eat;	// milliseconds
	uint64_t	time_to_sleep;	// milliseconds
	bool		must_eat;
	uint64_t	must_eat_count;
}	t_rules;

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex	mutex;
}	t_fork;

struct s_simulation;
typedef struct s_simulation t_simulation;
typedef struct s_philo
{
	uint64_t	start_time; // milliseconds since Epoch
	t_rules		*rules;
	uint16_t	id;
	pthread_t	thread;
	bool		alive;
	t_mutex		alive_mutex;
	uint64_t	eat_count;
	t_mutex		eat_count_mutex;
	t_fork		*left;
	t_fork		*right;
	uint64_t	last_meal_time;
	t_mutex		meal_time_mutex;
	bool		*should_log;
	t_simulation	*sim;
}	t_philo;

typedef struct s_simulation
{
	uint16_t		philo_count;
	t_rules			rules;
	uint64_t		start_time;
	bool			running;
	t_mutex			mutex;
	t_philo			*philos; // Array of philos
	t_fork			*forks; // Array of forks
}	t_simulation;

typedef enum e_status
{
	SUCCESS,
	E_MALLOC_FAILED,
	E_INVALID_ARG_COUNT,
	E_INVALID_ARG_TYPE,
	E_THREAD_FAILED
}	t_status;

t_status	initialize_simulation(t_simulation *simulation);
t_status	parse_args(int argc, char **argv, t_simulation *args);
void		handle_errors(t_status status);

// Timing
uint64_t	get_current_time(void);
uint64_t	get_time_since(uint64_t start_time);

// Individual philo
void		*philosophize(void *arg);
bool		philo_is_alive(t_philo *philo);
void		pick_up_fork(t_philo *philo, t_fork *fork);
void		philo_eating(t_philo *philo);
void		philo_sleeping(t_philo *philo);
void		philo_thinking(t_philo *philo);

// Monitoring philos
t_status	start_simulation(t_simulation *simulation);
t_status	monitor_philos(t_simulation *sim);
void		check_death(uint16_t count,
				t_philo *philos,
				bool *running,
				t_mutex *mutex);
void		*check_count(void *arg);
bool		philo_starved(t_philo *philo);
void		kill_philo(t_philo *philo);
void		kill_all_philos(uint16_t philo_count, t_philo *philos);

// Utils
void		log_message(const char *color, uint64_t time_stamp, t_philo *philo,
				const char *message);
void		ft_usleep(uint64_t target_time);
bool		simulation_is_running(t_simulation *simulation);
void		kill_philos(t_philo *starved, t_philo *philos, uint16_t count);
void		clean_up(t_simulation *simulation);

#endif