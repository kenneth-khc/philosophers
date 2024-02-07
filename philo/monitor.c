/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:57:56 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/07 23:48:25 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status	monitor_philos(t_simulation *sim)
{
	pthread_t	count_checker;
	uint16_t	i;

	if (sim->rules.must_eat)
		if (pthread_create(&count_checker, NULL, check_count, sim) != 0)
			return (E_THREAD_FAILED);
	while (simulation_is_running(sim))
		check_death(sim->philo_count, sim->philos, &sim->running, &sim->mutex);
	if (sim->rules.must_eat)
		pthread_join(count_checker, NULL);
	i = 0;
	while (i < sim->philo_count)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
	log_message(GREEN,
		get_time_since(sim->start_time), NULL, "Simulation ended");
	return (SUCCESS);
}

void	check_death(uint16_t philo_count, t_philo *philos, bool *running,
		t_mutex	*mutex)
{
	uint16_t	i;
	t_philo		*philo;

	i = 0;
	while (i < philo_count)
	{
		philo = &philos[i];
		if (philo_starved(philo))
		{
			pthread_mutex_lock(mutex);
			kill_philos(philo, philos, philo_count);
			*running = false;
			pthread_mutex_unlock(mutex);
			break ;
		}
		i++;
	}
}

bool	philo_starved(t_philo *philo)
{
	uint64_t	last_meal_time;
	uint64_t	time_to_die;
	bool		starved;

	pthread_mutex_lock(&philo->meal_time_mutex);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	time_to_die = philo->rules->time_to_die;
	starved = get_time_since(last_meal_time) > time_to_die;
	return (starved);
}

void	kill_philos(t_philo *starved_philo, t_philo *philos, uint16_t count)
{
	uint16_t	i;

	kill_philo(starved_philo);
	log_message(BOLD_RED,
		get_time_since(philos->start_time), starved_philo, "died");
	log_message(RED,
		get_time_since(philos->start_time), NULL, "Simulation ending");
	i = 0;
	while (i < count)
	{
		kill_philo(&philos[i]);
		i++;
	}
}

void	*check_count(void *arg)
{
	t_simulation	*simulation;
	t_philo			*philo;
	uint16_t		i;

	i = 0;
	simulation = (t_simulation *) arg;
	while (simulation_is_running(simulation) && i < simulation->philo_count)
	{
		philo = &simulation->philos[i];
		pthread_mutex_lock(&philo->eat_count_mutex);
		if (philo->eat_count < (uint64_t)simulation->rules.must_eat_count)
		{
			pthread_mutex_unlock(&philo->eat_count_mutex);
			continue ;
		}
		pthread_mutex_unlock(&philo->eat_count_mutex);
		i++;
	}
	pthread_mutex_lock(&simulation->mutex);
	simulation->running = false;
	printf("%llu ", get_time_since(simulation->start_time));
	if (i == simulation->philo_count)
		printf("All philos achieved eat count of %llu\n",
			simulation->rules.must_eat_count);
	kill_all_philos(simulation->philo_count, simulation->philos);
	pthread_mutex_unlock(&simulation->mutex);
	return (NULL);
}
