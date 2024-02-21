/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:45:11 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/21 21:37:31 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Return a philo's alive state */
bool	philo_is_alive(t_philo *philo)
{
	bool	alive;

	pthread_mutex_lock(&philo->alive_mutex);
	alive = philo->alive;
	pthread_mutex_unlock(&philo->alive_mutex);
	return (alive);
}

/* Return the simulation's running state */
bool	simulation_is_running(t_simulation *simulation)
{
	bool	running;

	pthread_mutex_lock(&simulation->mutex);
	running = simulation->running;
	pthread_mutex_unlock(&simulation->mutex);
	return (running);
}

void	turn_off_simulation(t_simulation *sim)
{
	pthread_mutex_lock(&sim->mutex);
	sim->running = false;
	pthread_mutex_unlock(&sim->mutex);
}
