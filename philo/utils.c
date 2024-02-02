/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 05:28:08 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/02 21:18:53 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	color_printf(const char *color, uint64_t timestamp,
 t_philosopher *philo, const char *message)
{
	if (philo == NULL)
		printf("%s%llu %s%s\n",
			color, timestamp, message, COLOR_RESET);
	else if (philo->should_log == false)
		return ;
	printf("%llu %s%d %s%s\n",
		timestamp, color, philo->id, message, COLOR_RESET);
	// else if (id == 0)
		// printf("%s%llu %s%s\n",
			// color, timestamp, message, COLOR_RESET);
}

bool	philo_is_alive(t_philosopher *philo)
{
	bool	alive;

	pthread_mutex_lock(&philo->alive_mutex);
	alive = philo->alive;
	return (pthread_mutex_unlock(&philo->alive_mutex), alive);
}

bool	simulation_is_running(t_simulation *simulation)
{
	bool	running;
	
	pthread_mutex_lock(&simulation->mutex);
	running = simulation->running;
	pthread_mutex_unlock(&simulation->mutex);
	return (running);
}

void	kill_philo(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->alive_mutex);
	philo->alive = false;
	pthread_mutex_unlock(&philo->alive_mutex);
}

void	kill_all_philos(uint16_t philo_count, t_philosopher *philos)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	while (i < philo_count)
	{
		philo = &philos[i];
		kill_philo(philo);
		i++;
	}
}

