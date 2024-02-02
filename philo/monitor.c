/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:57:56 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/02 21:10:26 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(uint16_t philo_count, t_philosopher *philos, bool *running,
		t_mutex	*mutex);
void	*check_count(void *arg);
		
void	monitor_philos(t_simulation *sim)
{
	int		i;

	i = 0;
	pthread_t	count_checker;
	if (sim->rules.min_eat != -1)
	{
		pthread_create(&count_checker, NULL, check_count, sim);
		pthread_detach(count_checker);
	}
	while (simulation_is_running(sim))
	{
		check_death(sim->philo_count, sim->philos, &sim->running, &sim->mutex);
	}
	color_printf(GREEN, get_time_since(sim->start_time), 0, "Simulation ended");
}

void	check_death(uint16_t philo_count, t_philosopher *philos, bool *running,
		t_mutex	*mutex)
{
	int	i;
	t_philosopher	*philo;
	// t_philosopher	*dead_philo;

	i = 0;
	while (i < philo_count)
	{
		philo = &philos[i];
		if (philo_starved(philo))
		{
			kill_philos(philo, philos, philo_count);
			pthread_mutex_lock(mutex);
			*running = false;
			pthread_mutex_unlock(mutex);
			// kill_philo(philo);
			// dead_philo = philo;
			// kill_all_philos(philo_count, philos);

			break ;
		}
		i++;
	}
}

void	kill_philos(t_philosopher *starved_philo, t_philosopher *philos, uint16_t count)
{
	int	i;

	kill_philo(starved_philo);
	color_printf(BOLD_RED,
		get_time_since(philos->start_time), starved_philo->id, "died");
	color_printf(RED,
		get_time_since(philos->start_time), 0, "Simulation ending");
	i = 0;
	while (i < count)
	{
		kill_philo(&philos[i]);
		i++;
	}	
}

bool	philo_starved(t_philosopher *philo)
{
	uint64_t	last_meal_time;
	uint64_t	time_to_die;

	pthread_mutex_lock(&philo->meal_time_mutex);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	time_to_die = philo->rules->time_to_die;
	bool dead = get_time_since(last_meal_time) > time_to_die;
	if (dead)
	{
		printf("Last meal time: %llu\n", last_meal_time);
		printf("Time to die: %llu\n", time_to_die);
		printf("Time since last meal: %llu\n", get_time_since(last_meal_time));
	}
	return (dead);
}

void	*check_count(void *arg)
{
	t_simulation	*simulation;
	t_philosopher	*philo;
	int				i;
	
	simulation = (t_simulation *) arg;
	i = 0;
	while (simulation_is_running(simulation))
	{
		while (i < simulation->philo_count)
		{
			philo = &simulation->philos[i];
			pthread_mutex_lock(&philo->eat_count_mutex);
			if (philo->eat_count < (uint64_t)simulation->rules.min_eat)
			{
				pthread_mutex_unlock(&philo->eat_count_mutex);
				continue ;
			}
			pthread_mutex_unlock(&philo->eat_count_mutex);
			i++;
		}
		kill_all_philos(simulation->philo_count, simulation->philos);
		pthread_mutex_lock(&simulation->mutex);
		simulation->running = false;
		pthread_mutex_unlock(&simulation->mutex);
	}
	return (NULL);	
}
