/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:45:11 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/27 19:55:44 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Return a philo's alive state */
bool	philo_is_alive(t_philo *philo)
{
	return (philo->alive);
}

/* Return the simulation's running state */
bool	simulation_is_running(t_simulation *simulation)
{
	bool	running;

	// sem_wait(simulation->gatekeeper);
	sem_post(simulation->temp);
	running = simulation->running;
	sem_wait(simulation->temp);
	// sem_post(simulation->gatekeeper);
	return (running);
}

void	turn_off_simulation(t_simulation *simulation)
{
	// sem_wait(simulation->gatekeeper);
	sem_post(simulation->temp);
	simulation->running = false;
	sem_wait(simulation->temp);
	// sem_post(simulation->gatekeeper);
}

#if 1
#include <signal.h>
void	flush_output(int signum)
{
	(void)signum;
	fflush(stdout);
	exit(EXIT_SUCCESS);
}

void	set_sigterm_handler(void)
{
	signal(SIGTERM, flush_output);
}
#endif