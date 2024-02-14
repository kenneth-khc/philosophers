/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:21:37 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/14 20:36:28 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
unpause_threads(t_simulation *sim);

t_status	start_simulation(t_simulation *sim)
{
	t_philo		*philo;
	uint16_t	i;

	i = 0;
	pthread_mutex_lock(&sim->mutex);
	while (i < sim->philo_count)
	{
		philo = &sim->philos[i];
		if (pthread_create(&philo->thread, NULL,
				philosophize, philo) != 0)
			return (E_THREAD_FAILED);
		i++;
	}
	unpause_threads(sim);
	return (SUCCESS);
}

static void	unpause_threads(t_simulation *sim)
{
	t_philo		*philo;
	uint16_t	i;

	sim->running = true;
	sim->start_time = get_current_time();
	i = 0;
	while (i < sim->philo_count)
	{
		philo = &sim->philos[i];
		philo->last_meal_time = sim->start_time;
		philo->death_time = philo->last_meal_time + philo->rules->time_to_die;
		i++;
	}
	log_message(GREEN, sim, "Simulation started");
	pthread_mutex_unlock(&sim->mutex);
}

void	log_message(const char *color, t_simulation *sim, const char *msg)
{
	uint64_t	timestamp;

	timestamp = get_time_since(sim->start_time);
	printf("%s%llu %s%s\n",
		color, timestamp, msg, COLOR_RESET);
}
