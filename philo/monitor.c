/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:57:56 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/19 15:44:42 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status	await_philos(t_simulation *sim)
{
	pthread_t	count_checker;
	t_philo		*philo;
	uint16_t	i;

	if (sim->rules.eat_limit)
	{
		if (pthread_create(&count_checker, NULL, check_count, sim) != 0)
			return (E_THREAD_FAILED);
		if (pthread_join(count_checker, NULL) != 0)
			return (E_JOIN_FAILED);
	}
	i = 0;
	while (i < sim->philo_count)
	{
		philo = &sim->philos[i];
		if (pthread_join(philo->thread, NULL) != 0)
			return (E_JOIN_FAILED);
		i++;
	}
	log_message(GREEN, sim, "Simulation ended");
	return (SUCCESS);
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
	sleep_ms(1);
	printf("%llu All philos ate at least %llu times\n",
			get_time_since(sim->start_time),
			sim->rules.required_meals);
	kill_all_philos(sim->philo_count, sim->philos);
	pthread_mutex_unlock(&sim->mutex);
}
