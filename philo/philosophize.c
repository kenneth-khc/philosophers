// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:14:02 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/20 00:36:07 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
pick_up_fork(t_philo *philo, t_fork *fork);

static void
philo_eating(t_philo *philo);

static void
philo_sleeping(t_philo *philo);

static void
philo_thinking(t_philo *philo);

void	*philosophize(void *arg)
{
	t_philo		*philo;
	pthread_t	monitor;

	philo = (t_philo *)(arg);
	pthread_create(&monitor, NULL, philo_monitor, philo);
	pthread_detach(monitor);
	pthread_mutex_lock(&philo->simulation->mutex);
	pthread_mutex_unlock(&philo->simulation->mutex);
	if (philo->left_fork == philo->right_fork)
	{
		sleep_ms(philo->rules->time_to_die);
		philo->alive = false;
	}
	if (philo->id % 2 == 0)
	{
		log_philo_action(YELLOW, philo, "is thinking");
		sleep_ms(50);
	}
	while (philo_is_alive(philo))
	{
		pick_up_fork(philo, philo->left_fork);
		pick_up_fork(philo, philo->right_fork);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}

static void	pick_up_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	log_philo_action(BLUE, philo, "has taken a fork");
}

static void	philo_eating(t_philo *philo)
{
	uint64_t	start_time;

	start_time = get_current_time();
	philo->last_meal_time = start_time;
	pthread_mutex_lock(&philo->death_time_mutex);
	philo->death_time = start_time + philo->rules->time_to_die;
	pthread_mutex_unlock(&philo->death_time_mutex);
	log_philo_action(MAGENTA, philo, "is eating");
	sleep_ms(philo->rules->time_to_eat);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

static void	philo_sleeping(t_philo *philo)
{
	log_philo_action(CYAN, philo, "is sleeping");
	sleep_ms(philo->rules->time_to_sleep);
}

static void	philo_thinking(t_philo *philo)
{
	// uint64_t	time_to_eat;
	// uint64_t	time_to_sleep;
	// uint64_t	time_to_think;
	// uint64_t	start_time;
	// uint64_t	end_time;

	// time_to_eat = philo->rules->time_to_eat;
	// time_to_sleep = philo->rules->time_to_sleep;

	// if (time_to_eat - time_to_sleep > 0)
	// 	time_to_think = time_to_eat - time_to_sleep;
	// else
	// 	time_to_think = 0;
	// start_time = get_current_time();
	// end_time = start_time + time_to_think;
	// log_philo_action(YELLOW, philo, "is thinking");
	// if (end_time < philo->death_time)
	// 	sleep_ms(time_to_think);
	// else
	// 	sleep_to_death(philo, philo->simulation, start_time);
	log_philo_action(YELLOW, philo, "is thinking");
}
