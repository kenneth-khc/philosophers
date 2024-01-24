/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:10:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/24 20:55:05 by kecheong         ###   ########.fr       */
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

#define BLK "\e[0;30m"
#define MAG "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define RED "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"

typedef struct s_rules
{
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
	uint32_t	min_eat;	
}	t_rules;

typedef struct s_philosopher
{
	uint32_t	start_time;
	t_rules		rules;
	int			id;
	pthread_t	thread;
	int			state;
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
	uint32_t	last_meal_time;
}	t_philosopher;

typedef struct s_simulation
{
	int			philo_count;
	t_rules		rules;
	uint32_t	start_time;
	t_philosopher	*philos;
	pthread_mutex_t	*forks;
}	t_simulation;

enum
{
	EATING,
	THINKING,
	SLEEPING
};

void	parse_args(int argc, char **argv, t_simulation *args);
void	init_philos(t_philosopher **philos, t_simulation *args);
void	init_mutexes(pthread_mutex_t *forks, int count);
void	init_hands(t_philosopher *philo, t_simulation *sim);

// Timing
void	sleep_seconds(unsigned int seconds);
void	sleep_millisecond(unsigned int milliseconds);
uint32_t	get_program_time(uint32_t start_time);

// Individual philo
bool	philo_is_alive(t_philosopher *philo);
void	pick_up_left_fork(t_philosopher *philo);
void	pick_up_right_fork(t_philosopher *philo);
void	munch_munch(t_philosopher *philo);
void	philo_sleeping(t_philosopher *philo);


#endif