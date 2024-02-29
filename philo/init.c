/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:24:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/23 11:52:05 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status
init_philos(t_simulation *sim);

static t_status
init_mutexes(t_simulation *sim);

static void	
assign_forks(t_philo *philos, t_fork *forks, uint16_t count);

/* Initialize the simulation to be run but keep the threads paused */
t_status	init_simulation(t_simulation *sim)
{
	t_status	status;

	sim->running = false;
	status = init_philos(sim);
	if (status == SUCCESS)
		status = init_mutexes(sim);
	if (status == SUCCESS)
		assign_forks(sim->philos, sim->forks, sim->philo_count);
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
	return (SUCCESS);
}

/* Initializes mutexes to protect critical sections between threads */
static t_status	init_mutexes(t_simulation *sim)
{
	t_philo		*philo;
	t_fork		*fork;
	uint16_t	i;

	sim->forks = malloc(sizeof(t_fork) * sim->philo_count);
	if (sim->forks == NULL)
		return (E_MALLOC_FAILED);
	i = 0;
	while (i < sim->philo_count)
	{
		philo = &sim->philos[i];
		pthread_mutex_init(&philo->alive_mutex, NULL);
		pthread_mutex_init(&philo->eat_count_mutex, NULL);
		pthread_mutex_init(&philo->death_time_mutex, NULL);
		fork = &sim->forks[i];
		pthread_mutex_init(&fork->mutex, NULL);
		i++;
	}
	pthread_mutex_init(&sim->mutex, NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
	return (SUCCESS);
}

/**
 * Assign left and right forks to a philo.
 * Philo n will have Fork n in its left hand and Fork n+1 in its right
 */
static void	assign_forks(t_philo *philos, t_fork *forks, uint16_t count)
{
	t_philo		*philo;
	uint16_t	i;

	i = 0;
	while (i < count)
	{
		philo = &philos[i];
		philo->left_fork = &forks[i];
		philo->right_fork = &forks[(i + 1) % count];
		if (philo->left_fork == philo->right_fork)
			philo->alive = false;
		i++;
	}
}
