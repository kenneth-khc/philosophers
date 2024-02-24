/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:14:02 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/24 20:59:50 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void
pick_up_fork(t_philo *philo, sem_t *forks);

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

	(void)arg;
	philo = (t_philo *)arg;
	
	philo->forks = philo->simulation->forks;
	if (pthread_create(&monitor, NULL, philo_monitor, philo) != 0)
		error_and_exit(E_THREAD_FAILED);
	if (philo->id % 2 != 0)
	{
		log_philo_action(YELLOW, philo, "is thinking");
		sleep_ms(philo->simulation->rules.time_to_eat / 2);
	}
	while (philo_is_alive(philo))
	{
		pick_up_fork(philo, philo->forks);
		pick_up_fork(philo, philo->forks);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	if (pthread_join(monitor, NULL) != 0)
		error_and_exit(E_JOIN_FAILED);
	exit(EXIT_SUCCESS);
}

static void	pick_up_fork(t_philo *philo, sem_t *forks)
{
	sem_wait(forks);
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
	// pthread_mutex_lock(&philo->death_time_mutex);
	philo->death_time = start_time + philo->rules->time_to_die;
	// pthread_mutex_unlock(&philo->death_time_mutex);
	log_philo_action(CYAN, philo, "is eating");
	sleep_ms(philo->rules->time_to_eat);
	if (philo->rules->eat_limit)
	{
		philo->eat_count++;
		if (philo->eat_count == philo->rules->required_meals)
			sem_post(philo->simulation->eat_counter);
	}
	sem_post(philo->forks);
	sem_post(philo->forks);
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
