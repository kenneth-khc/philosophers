/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/29 17:25:39 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;
	enum e_status	status;

	status = parse_args(argc, argv, &simulation);
	if (status != SUCCESS)
	{
		handle_error(status);
		return (1);
	}
	status = validate_rules(&simulation.rules, argv);
	if (status != SUCCESS)
	{
		handle_error(status);
		return (1);
	}
	status = init_philos(&simulation.philos, &simulation);
	if (status != SUCCESS)
	{
		handle_error(status);
		return (1);
	}
	if (!init_mutexes(&simulation.philos, &simulation.forks, simulation.philo_count))
		return (1);
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
