/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/01 02:06:17 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
	t_status		status;

	status = parse_args(argc, argv, &sim);
	if (status == SUCCESS)
		status = validate_rules(&sim, argv);
	if (status == SUCCESS)
		status = init_philos(&sim.philos, &sim);
	// if (status == SUCCESS)
	// 	status = init_mutexes(&sim.philos, &sim.forks, sim.philo_count);
	if (status == SUCCESS)
		status = init_muts(&sim, &sim.philos, sim.philo_count);
	if (status == SUCCESS)
		status = start_simulation(sim.philos, sim.philo_count, sim.start_time);
	if (status != SUCCESS)
	{
		handle_errors(status);
		return (1);
	}
	monitor_philos(&sim);
	return (SUCCESS);
}

t_status	start_simulation(
		t_philosopher *philos, uint16_t philo_count, uint64_t start_time)
{
	int	i;

	i = 0;
	// color_printf(GREEN, start_time, 0, "Simulation started");
	color_printf(GREEN, get_time_since(start_time), 0, "Simulation started");
	while (i < philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philosophize, &philos[i]) != 0)
			return (E_THREAD_FAILED);
		i++;
	}
	return (SUCCESS);
}

t_status init_muts(t_simulation *sim,
	t_philosopher **philos, uint16_t philo_count)
{
	uint16_t		i;
	t_philosopher	*philo;
	
	sim->fork_arr = malloc(sizeof(t_fork) * philo_count);
	if (!sim->fork_arr)
		return (E_MALLOC_FAILED);
	i = 0;
	while (i < philo_count)
	{
		philo = &(*philos)[i];
		pthread_mutex_init(&philo->state_mutex, NULL);
		pthread_mutex_init(&philo->alive_mutex, NULL);
		pthread_mutex_init(&philo->time_mutex, NULL);
		pthread_mutex_init(&philo->eat_count_mutex, NULL);
		// pthread_mutex_init(&(*forks)[i], NULL);
		pthread_mutex_init(&sim->fork_arr[i].mutex, NULL);
		pthread_mutex_init(&sim->fork_arr[i].picked_up_mutex, NULL);
		i++;
	}
	init_hands(philos, sim->fork_arr, philo_count);
	return (SUCCESS);
}
