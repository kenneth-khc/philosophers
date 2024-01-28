/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/28 23:55:57 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (!parse_args(argc, argv, &simulation))
		return (1);
	// simulation.philos = malloc(sizeof(*simulation.philos) * simulation.philo_count);
	// simulation.forks = malloc(sizeof(*simulation.forks) * simulation.philo_count);
	if (!init_philos(&simulation.philos, &simulation))
		return (1);
	if (!init_mutexes(&simulation.philos, &simulation.forks, simulation.philo_count))
		return (1);
	// int i = 0;
	start_simulation(simulation.philos, simulation.philo_count, simulation.start_time);
	monitor_philos(&simulation);
}

void	start_simulation(
		t_philosopher *philos, uint16_t philo_count, uint64_t start_time)
{
	int	i;

	i = 0;
	color_printf(GREEN, start_time, 0, "Simulation started");
	while (i < philo_count)
	{
		pthread_create(&philos[i].thread, NULL, philosophize, &philos[i]);
		i++;
	}	
}
