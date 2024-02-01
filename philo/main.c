/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/01 08:50:49 by kecheong         ###   ########.fr       */
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
		status = init_muts(&sim, &sim.philos, sim.philo_count);
	if (status == SUCCESS)
		status = start_simulation(sim.philos, sim.philo_count, sim.start_time);
	if (status != SUCCESS)
		return (handle_errors(status), EXIT_FAILURE);
	monitor_philos(&sim);
	return (SUCCESS);
}

t_status	start_simulation(
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
		i++;
	}
	return (SUCCESS);
}
