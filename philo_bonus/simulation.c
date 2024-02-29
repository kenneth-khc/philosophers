/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:21:37 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/29 21:56:04 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void
init_philo(t_simulation *sim);

static void
fork_philos(t_simulation *sim);

/* Create threads to run each philosopher's routine */
void	start_simulation(t_simulation *sim)
{
	uint16_t	i;

	sim->pids = malloc(sizeof(pid_t) * sim->philo_count);
	if (sim->pids == NULL)
		error_and_exit(E_MALLOC_FAILED);
	init_philo(sim);
	log_message(GREEN, sim, "Simulation started");
	fork_philos(sim);
	i = 0;
}

static void	init_philo(t_simulation *sim)
{
	t_philo	*philo;

	philo = &sim->philo;
	philo->simulation = sim;
	philo->rules = &sim->rules;
	philo->eat_count = 0;
	if (sim->philo_count > 1)
		philo->alive = true;
	else
		philo->alive = false;
	sim->start_time = get_current_time();
}

static void	fork_philos(t_simulation *sim)
{
	pid_t		pid;
	uint16_t	i;

	i = 0;
	while (i < sim->philo_count)
	{
		sim->philo.id = i + 1;
		sim->philo.mealtime_semaphore = sim->mealtime_semaphores[i];
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			philosophize(&sim->philo);
		else
			sim->pids[i] = pid;
		i++;
	}
}
