/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 22:41:31 by kecheong          #+#    #+#             */
/*   Updated: 2024/03/01 12:21:48 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Main thread waits for philos and its monitors to finish running */
t_status	await_philos(t_simulation *sim)
{
	pthread_t	count_checker;
	t_philo		*philo;
	uint16_t	i;

	if (sim->rules.eat_limit && sim->philo_count > 0)
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

/* Check each philo's eat count and terminate if all philos satisfied */
void	*check_count(void *arg)
{
	t_simulation	*simulation;
	t_philo			*philo;
	uint64_t		target_meals;
	uint16_t		i;

	i = 0;
	simulation = (t_simulation *)arg;
	target_meals = simulation->rules.required_meals;
	while (simulation_is_running(simulation) && i < simulation->philo_count)
	{
		philo = &simulation->philos[i];
		pthread_mutex_lock(&philo->eat_count_mutex);
		if (philo->eat_count >= target_meals)
			i++;
		pthread_mutex_unlock(&philo->eat_count_mutex);
	}
	if (i == simulation->philo_count)
	{
		turn_off_simulation(simulation);
		printf("%*u%s All philos ate at least %llu times%s\n", PADDING,
			get_time_since(simulation->start_time), GREEN,
			simulation->rules.required_meals, COLOR_RESET);
		kill_philos(simulation);
	}
	return (NULL);
}
