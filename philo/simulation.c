/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:21:37 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/21 23:46:19 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
unpause_threads(t_simulation *sim);

/* Create threads to run each philosopher's routine */
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

/* Starts the simulation once all threads are successfully created */
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

/* Log general simulation messages */
void	log_message(const char *color, t_simulation *sim, const char *msg)
{
	uint32_t	timestamp;

	pthread_mutex_lock(&sim->print_mutex);
	timestamp = get_time_since(sim->start_time);
	printf("%*u%s %s%s\n", PADDING,
		timestamp, color, msg, COLOR_RESET);
	pthread_mutex_unlock(&sim->print_mutex);
}

/* Log a philo's action */
void	log_philo_action(const char *color, t_philo *philo, const char *msg)
{
	t_simulation	*sim;
	uint32_t		timestamp;

	sim = philo->simulation;
	pthread_mutex_lock(&sim->print_mutex);
	if (simulation_is_running(sim) && philo_is_alive(philo))
	{
		timestamp = get_time_since(sim->start_time);
		printf("%*u%s %d %s%s\n", PADDING,
			timestamp, color, philo->id, msg, COLOR_RESET);
	}
	pthread_mutex_unlock(&sim->print_mutex);
}

/* Log a philo's death */
void	log_philo_death(const char *color, t_simulation *sim, uint16_t id)
{
	uint32_t	timestamp;

	pthread_mutex_lock(&sim->print_mutex);
	if (simulation_is_running(sim))
	{
		turn_off_simulation(sim);
		timestamp = get_time_since(sim->start_time);
		printf("%*u%s %d %s%s\n", PADDING,
			timestamp, color, id, "died", COLOR_RESET);
	}
	pthread_mutex_unlock(&sim->print_mutex);
}
