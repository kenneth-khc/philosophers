/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:38:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/20 23:44:05 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_monitor(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->simulation->mutex);
	pthread_mutex_unlock(&philo->simulation->mutex);
	while (philo_is_alive(philo))
	{
		sleep_ms(1);
		if (philo_starved(philo))
		{
			kill_philo(philo);
			kill_all_philos(philo->simulation->philo_count, philo->simulation->philos);
			log_philo_death(RED, philo->simulation, philo->id);
		}
	}
	return (NULL);
}

void	turn_off_simulation(t_simulation *sim)
{
	pthread_mutex_lock(&sim->mutex);
	sim->running = false;
	pthread_mutex_unlock(&sim->mutex);
}

bool	philo_starved(t_philo *philo)
{
	bool	starved;

	pthread_mutex_lock(&philo->death_time_mutex);
	starved = get_current_time() > philo->death_time;
	pthread_mutex_unlock(&philo->death_time_mutex);
	return (starved);
}