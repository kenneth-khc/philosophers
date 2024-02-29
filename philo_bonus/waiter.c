/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:25:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/29 22:00:57 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Main thread waits for philos and its monitors to finish running */
void	await_philos(t_simulation *sim)
{
	pid_t		checker_pid;
	uint16_t	i;

	if (sim->rules.eat_limit == true)
	{
		checker_pid = fork();
		if (checker_pid == -1)
			error_and_exit(E_FORK_FAILED);
		else if (checker_pid == 0)
			check_count(sim);
	}
	waitpid(-1, NULL, 0);
	i = 0;
	while (i < sim->philo_count)
	{
		kill(sim->pids[i], SIGTERM);
		i++;
	}
	if (sim->rules.eat_limit == true)
		kill(checker_pid, SIGTERM);
	log_message(GREEN, sim, "Simulation ended");
}

/* Check each philo's eat count and terminate if all philos satisfied */
void	*check_count(void *arg)
{
	t_simulation	*sim;
	uint16_t		philos_satisfied;

	sim = (t_simulation *)arg;
	philos_satisfied = 0;
	while (philos_satisfied < sim->philo_count)
	{
		sem_wait(sim->eat_counter);
		philos_satisfied++;
	}
	sem_wait(sim->printer);
	printf("%*u%s All philos ate at least %llu times%s\n", PADDING,
		get_time_since(sim->start_time), GREEN,
		sim->rules.required_meals, COLOR_RESET);
	exit(EXIT_SUCCESS);
}
