/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 05:28:08 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/20 17:02:24 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_philo_action(const char *color, t_philo *philo, const char *msg)
{
	uint64_t	timestamp;

	if (simulation_is_running(philo->simulation) && philo_is_alive(philo))
	{
		timestamp = get_time_since(philo->simulation->start_time);
		printf("%llu %s%d %s%s\n",
			timestamp, color, philo->id, msg, COLOR_RESET);
	}
}

void	log_philo_death(const char *color, t_simulation *sim, uint16_t id)
{
	uint64_t	timestamp;

	pthread_mutex_lock(&sim->print_lock);
	if (simulation_is_running(sim))
	{
		pthread_mutex_lock(&sim->mutex);
		sim->running = false;
		pthread_mutex_unlock(&sim->mutex);
		timestamp = get_time_since(sim->start_time);
		printf("%llu %s%d %s%s\n", timestamp, color, id, "died", COLOR_RESET);
	}
	pthread_mutex_unlock(&sim->print_lock);
}

bool	philo_is_alive(t_philo *philo)
{
	bool	alive;

	pthread_mutex_lock(&philo->alive_mutex);
	alive = philo->alive;
	pthread_mutex_unlock(&philo->alive_mutex);
	return (alive);
}

bool	simulation_is_running(t_simulation *simulation)
{
	bool	running;

	pthread_mutex_lock(&simulation->mutex);
	running = simulation->running;
	pthread_mutex_unlock(&simulation->mutex);
	return (running);
}

void	kill_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->alive_mutex);
	philo->alive = false;
	pthread_mutex_unlock(&philo->alive_mutex);
}

void	kill_all_philos(uint16_t philo_count, t_philo *philos)
{
	uint16_t	i;
	t_philo		*philo;

	i = 0;
	while (i < philo_count)
	{
		philo = &philos[i];
		kill_philo(philo);
		i++;
	}
}

void	kill_philos(t_philo *philos, uint16_t philo_count)
{
	t_philo		*philo;
	uint16_t	i;

	i = 0;
	while (i < philo_count)
	{
		philo = &philos[i];
		pthread_mutex_lock(&philo->alive_mutex);
		philo->alive = false;
		pthread_mutex_unlock(&philo->alive_mutex);
		i++;
	}
}
