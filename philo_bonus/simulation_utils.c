/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:45:11 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/24 17:32:54 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Return a philo's alive state */
bool	philo_is_alive(t_philo *philo)
{
	bool	alive;

	alive = philo->alive;
	return (alive);
}

/* Return the simulation's running state */
// bool	simulation_is_running(t_simulation *simulation)
// {
// 	bool	running;

// 	sem_wait(simulation->master_lock);
// 	running = simulation->running;
// 	sem_post(simulation->master_lock);
// 	return (running);
// }

// void	turn_off_simulation(t_simulation *simulation)
// {
// 	sem_wait(simulation->master_lock);
// 	simulation->running = false;
// 	sem_post(simulation->master_lock);
// }
