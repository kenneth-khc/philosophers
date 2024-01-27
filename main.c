/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/27 10:14:35 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
	
	parse_args(argc, argv, &sim);
	printf(GRN"%.10llu Simulation started\n"COLOR_RESET, get_time_since(sim.start_time));
	// color_printf(GRN, sim.start_time, 0, "Simulation started\n");
	sim.philos = malloc(sizeof(*sim.philos) * sim.philo_count);
	sim.forks = malloc(sizeof(*sim.forks) * sim.philo_count);
	init_mutexes(sim.philos, sim.forks, sim.philo_count);

	init_philos(&sim.philos, &sim);
	
	monitor_philos(&sim);
}
