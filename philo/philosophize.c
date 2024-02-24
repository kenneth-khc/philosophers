/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:14:02 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/23 10:38:31 by kecheong         ###   ########.fr       */
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

/* Eat, sleep, think, ~code~, repeat. */
void	*philosophize(void *arg)
{
	t_philo		*philo;
	pthread_t	monitor;

	philo = (t_philo *)(arg);
	if (pthread_create(&monitor, NULL, philo_monitor, philo) != 0)
		return (NULL);
	pthread_mutex_lock(&philo->simulation->mutex);
	pthread_mutex_unlock(&philo->simulation->mutex);
	if (philo->id % 2 == 0)
	{
		log_philo_action(YELLOW, philo, "is thinking");
		sleep_ms(philo->simulation->rules.time_to_eat / 2);
	}
	while (philo_is_alive(philo))
	{
		pick_up_fork(philo, philo->left_fork);
		pick_up_fork(philo, philo->right_fork);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	pthread_join(monitor, NULL);
	return (NULL);
}

static void	pick_up_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	log_philo_action(BLUE, philo, "has taken a fork");
}

/**
 * Calculate philo's starvation time, increment its eat count
 * and put down forks once done eating
 */
static void	philo_eating(t_philo *philo)
{
	uint64_t	start_time;

	start_time = get_current_time();
	philo->last_meal_time = start_time;
	pthread_mutex_lock(&philo->death_time_mutex);
	philo->death_time = start_time + philo->rules->time_to_die;
	pthread_mutex_unlock(&philo->death_time_mutex);
	log_philo_action(CYAN, philo, "is eating");
	sleep_ms(philo->rules->time_to_eat);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

static void	philo_sleeping(t_philo *philo)
{
	log_philo_action(MAGENTA, philo, "is sleeping");
	sleep_ms(philo->rules->time_to_sleep);
}

static void	philo_thinking(t_philo *philo)
{
	log_philo_action(BLACK, philo, "is thinking");
}
