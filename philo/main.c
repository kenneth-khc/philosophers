/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/06 18:05:23 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
	t_status		status;

	status = parse_args(argc, argv, &sim);
	if (status == SUCCESS)
		status = initialize_simulation(&sim);
	if (status == SUCCESS)
		status = start_simulation(&sim);
	if (status == SUCCESS)
		status = monitor_philos(&sim);
	handle_errors(status);
	// system("leaks -q philo");
	return (status);
}

t_status	start_simulation(t_simulation *simulation)
{
	uint16_t	i;
	t_philo		*philos;
	
	i = 0;
	philos = simulation->philos;
	simulation->running = false;
	while (i < simulation->philo_count)
	{
		// philos[i].start_time = simulation->start_time;
		// philos[i].last_meal_time = simulation->start_time;
		if (pthread_create(&philos[i].thread, NULL,
				philosophize, &philos[i]) != 0)
			return (E_THREAD_FAILED);
		pthread_detach(philos[i].thread);
		i++;
	}
	pthread_mutex_lock(&simulation->mutex);
	simulation->running = true;
	pthread_mutex_unlock(&simulation->mutex);
	simulation->start_time = get_current_time();
	log_message(GREEN, 
		get_time_since(simulation->start_time), NULL, "Simulation started");
	return (SUCCESS);
}
