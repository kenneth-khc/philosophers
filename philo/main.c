/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/02 20:38:32 by kecheong         ###   ########.fr       */
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
	if (status == SUCCESS)
		status = init_mutexes(&sim, &sim.philos, sim.philo_count);
	if (status == SUCCESS)
		// status = start_simulation(sim.philos, sim.philo_count, sim.start_time);
		status = start_simulation(&sim);
	if (status != SUCCESS)
		return (handle_errors(status), EXIT_FAILURE);
	monitor_philos(&sim);
	system("leaks -q philo");
	return (SUCCESS);
}

t_status	start_simulation(t_simulation *simulation)
{
	int				i;
	uint64_t		start_time;
	t_philosopher	*philos;
	
	i = 0;
	philos = simulation->philos;
	simulation->running = true;
	start_time = simulation->start_time;
	color_printf(GREEN, get_time_since(start_time), 0, "Simulation started");
	while (i < simulation->philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philosophize, &philos[i]) != 0)
			return (E_THREAD_FAILED);
		pthread_detach(philos[i].thread);
		i++;
	}
	return (SUCCESS);
}

t_status	start_simulation1(
		t_philosopher *philos, uint16_t philo_count, uint64_t start_time)
{
	int	i;

	i = 0;
	color_printf(GREEN, get_time_since(start_time), 0, "Simulation started");
	while (i < philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philosophize, &philos[i]) != 0)
			return (E_THREAD_FAILED);
		pthread_detach(philos[i].thread);
		i++;
	}
	return (SUCCESS);
}
