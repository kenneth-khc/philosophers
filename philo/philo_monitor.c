/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:38:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/21 21:41:00 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* A secondary thread to monitor whether it's philo has starved or not */
void	*philo_monitor(void	*arg)
{
	t_philo			*philo;
	t_simulation	*sim;

	philo = (t_philo *)arg;
	sim = philo->simulation;
	pthread_mutex_lock(&philo->simulation->mutex);
	pthread_mutex_unlock(&philo->simulation->mutex);
	if (philo_is_alive(philo) == false)
	{
		sleep_ms(sim->rules.time_to_die);
		log_philo_death(BOLD_RED, sim, philo->id);
	}
	while (philo_is_alive(philo))
	{
		sleep_ms(1);
		if (philo_starved(philo))
		{
			kill_philo(philo);
			log_philo_death(BOLD_RED, sim, philo->id);
			kill_philos(sim);
		}
	}
	return (NULL);
}

/* Get current time and compare it with philo's starvation time */
bool	philo_starved(t_philo *philo)
{
	bool	starved;

	pthread_mutex_lock(&philo->death_time_mutex);
	starved = get_current_time() > philo->death_time;
	pthread_mutex_unlock(&philo->death_time_mutex);
	return (starved);
}

void	kill_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->alive_mutex);
	philo->alive = false;
	pthread_mutex_unlock(&philo->alive_mutex);
}

void	kill_philos(t_simulation *sim)
{
	t_philo		*philo;
	uint16_t	i;
	uint16_t	count;

	i = 0;
	count = sim->philo_count;
	while (i < count)
	{
		philo = &sim->philos[i];
		kill_philo(philo);
		i++;
	}
}
