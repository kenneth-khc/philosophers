/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 05:28:08 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/06 18:13:25 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_message(const char *color, uint64_t timestamp,
 t_philo *philo, const char *message)
{
	if (philo == NULL)
	{
		printf("%s%llu %s%s\n",
			color, timestamp, message, COLOR_RESET);
		return ;	
	}
	if (*philo->should_log == false)
		return ;
	else
	{
		printf("%llu %s%d %s%s\n",
			timestamp, color, philo->id, message, COLOR_RESET);
	}
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
	int				i;
	t_philo	*philo;

	i = 0;
	while (i < philo_count)
	{
		philo = &philos[i];
		kill_philo(philo);
		i++;
	}
}

