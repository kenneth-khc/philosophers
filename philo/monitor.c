/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:57:56 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/29 23:18:37 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_philos(t_simulation *sim)
{
	int		i;
	bool	simulation_running;

	i = 0;
	simulation_running = true;
	while (simulation_running)
	{
		simulation_running = check_philos_death(sim->philo_count, sim->philos);
		if (sim->rules.min_eat != -1 && simulation_running)
			simulation_running = check_eat_count(sim->philo_count, sim->philos);
	}
	while (i < sim->philo_count)
	{
		pthread_join((sim->philos)[i].thread, NULL);
		i++;
	}
	color_printf(GREEN, sim->start_time, 0, "Simulation ended");
}

bool	check_philos_death(uint16_t philo_count, t_philosopher *philos)
{
	int				i;
	t_philosopher	*philo;
	t_philosopher	*dead_philo;
	bool			simulation_running;

	i = 0;
	simulation_running = true;
	while (i < philo_count)
	{
		philo = &philos[i];
		if (philo_starved(philo))
		{
			dead_philo = philo;
			kill_philo(philo);
			simulation_running = false;
			kill_all_philos(philo_count, philos);
			color_printf(BOLD_RED, philos->start_time, dead_philo->id, "died");
			color_printf(RED, philos->start_time, 0, "Simulation ending");
			break ;
		}
		i++;
	}
	return (simulation_running);
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

bool	philo_starved(t_philosopher *philo)
{
	uint64_t	last_meal_time;
	uint64_t	time_to_die;

	pthread_mutex_lock(&philo->time_mutex);
	last_meal_time = philo->last_meal_time;
	time_to_die = philo->rules.time_to_die;
	pthread_mutex_unlock(&philo->time_mutex);
	return (get_time_since(last_meal_time) > time_to_die);
}
