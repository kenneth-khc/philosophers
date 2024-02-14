/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:57:56 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/17 23:11:03 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status	monitor_philos(t_simulation *sim)
{
	pthread_t	count_checker;
	uint16_t	i;

	if (sim->rules.eat_limit)
		if (pthread_create(&count_checker, NULL, check_count, sim) != 0)
			return (E_THREAD_FAILED);
	if (sim->rules.eat_limit)
		pthread_join(count_checker, NULL);
	i = 0;
	while (i < sim->philo_count)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
	log_message(GREEN, sim, "Simulation ended");
	return (SUCCESS);
}

void	kill_philos(t_philo *starved_philo, t_philo *philos, uint16_t count)
{
	uint16_t	i;

	kill_philo(starved_philo);
	// log_philo_death(RED, philos->simulation, starved_philo->id);
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
	uint64_t		target_meals;
	uint16_t		i;

	i = 0;
	simulation = (t_simulation *)arg;
	target_meals = (uint64_t)simulation->rules.required_meals;
	while (simulation_is_running(simulation) && i < simulation->philo_count)
	{
		philo = &simulation->philos[i];
		pthread_mutex_lock(&philo->eat_count_mutex);
		if (philo->eat_count >= target_meals)
			i++;
		pthread_mutex_unlock(&philo->eat_count_mutex);
	}
	if (i == simulation->philo_count)
		log_and_terminate(simulation);
	return (NULL);
}

void	log_and_terminate(t_simulation *sim)
{
	pthread_mutex_lock(&sim->mutex);
	sim->running = false;
	printf("%llu All philos ate at least %llu times\n",
			get_time_since(sim->start_time),
			sim->rules.required_meals);
	kill_all_philos(sim->philo_count, sim->philos);
	pthread_mutex_unlock(&sim->mutex);
}

// void	check_death(t_philo *philos, t_simulation *sim)
// {
// 	uint16_t	i;
// 	t_philo		*philo;

// 	i = 0;
// 	while (i < sim->philo_count)
// 	{
// 		philo = &philos[i];
// 		// if (philo_starved(philo))
// 		if (philo->alive == false)
// 		{
// 			pthread_mutex_lock(&sim->mutex);
// 			kill_philos(philo, philos, sim->philo_count);
// 			sim->running = false;
// 			pthread_mutex_unlock(&sim->mutex);
// 			break ;
// 		}
// 		i++;
// 		if (i == sim->philo_count)
// 			i = 0;
// 	}
// }

// bool	philo_starved(t_philo *philo)
// {
// 	uint64_t	last_meal_time;
// 	uint64_t	time_to_die;
// 	bool		starved;

// 	pthread_mutex_lock(&philo->meal_time_mutex);
// 	last_meal_time = philo->last_meal_time;
// 	pthread_mutex_unlock(&philo->meal_time_mutex);
// 	time_to_die = philo->rules->time_to_die;
// 	starved = get_time_since(last_meal_time) > time_to_die;
// 	return (starved);
// }