/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:24:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/22 09:08:57 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_status
init_philos(t_simulation *sim);

// static t_status
// init_mutexes(t_simulation *sim);

static t_status init_semaphores(t_simulation *sim);

// static void	
// assign_forks(t_philo *philos, t_fork *forks, uint16_t count);

/* Initialize the simulation to be run but keep the threads paused */
t_status	initialize_simulation(t_simulation *sim)
{
	t_status	status;

	sim->running = true;
	status = init_philos(sim);
	if (status == SUCCESS)
		status = init_semaphores(sim);
	// if (status == SUCCESS)
		// assign_forks(sim->philos, sim->forks, sim->philo_count);
	return (status);
}

/* Initializes philos and sets their id and state to alive */
static t_status	init_philos(t_simulation *sim)
{
	t_philo		*philo;
	uint16_t	i;

	sim->philos = malloc(sizeof(t_philo) * sim->philo_count);
	if (sim->philos == NULL)
		return (E_MALLOC_FAILED);
	i = 0;
	while (i < sim->philo_count)
	{
		philo = &sim->philos[i];
		philo->simulation = sim;
		philo->rules = &sim->rules;
		philo->id = i + 1;
		philo->alive = true;
		philo->eat_count = 0;
		i++;
	}
	if (sim->philo_count == 1)
		philo->alive = false;
	return (SUCCESS);
}

static t_status init_semaphores(t_simulation *sim)
{
	(void)sim;
	sem_unlink("FORKS");
	sim->forks = sem_open("FORKS", O_CREAT, 0666, sim->philo_count);
	sem_unlink("MASTER");
	sim->master_lock = sem_open("MASTER", O_CREAT, 0666, 1);
	sem_unlink("PRINTER");
	sim->printer = sem_open("PRINTER", O_CREAT, 0666, 1);
	sem_unlink("EAT_COUNTER");
	sim->eat_counter = sem_open("EAT_COUNTER", O_CREAT, 0666, 0);

	return (SUCCESS);
}

/**
 * Assign left and right forks to a philo.
 * Philo n will have Fork n in its left hand and Fork n+1 in its right
 */
// static void	assign_forks(t_philo *philos, t_fork *forks, uint16_t count)
// {
// 	t_philo		*philo;
// 	uint16_t	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		philo = &philos[i];
// 		philo->left_fork = &forks[i];
// 		philo->right_fork = &forks[(i + 1) % count];
// 		if (philo->left_fork == philo->right_fork)
// 			philo->alive = false;
// 		i++;
// 	}
// }

/* Initializes mutexes to protect critical sections between threads */
// static t_status	init_mutexes(t_simulation *sim)
// {
// 	t_philo		*philo;
// 	uint16_t	i;

// 	i = 0;
// 	while (i < sim->philo_count)
// 	{
// 		philo = &sim->philos[i];
// 		i++;
// 	}
// 	return (SUCCESS);
// }
