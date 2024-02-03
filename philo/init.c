/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:24:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/03 22:31:15 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status
init_philos(t_simulation *sim);

static t_status
init_mutexes(t_simulation *sim);

static void	
assign_forks(t_philo *philos, t_fork *forks, uint16_t count);

t_status	initialize_simulation(t_simulation *simulation)
{
	t_status	status;

	status = init_philos(simulation);
	if (status == SUCCESS)
		status = init_mutexes(simulation);
	return (status);
}

static t_status	init_philos(t_simulation *sim)
{
	uint16_t	i;
	t_philo		*philo;

	i = 0;
	sim->philos = malloc(sizeof(t_philo) * sim->philo_count);
	if (sim->philos == NULL)
		return (E_MALLOC_FAILED);
	while (i < sim->philo_count)
	{
		philo = &sim->philos[i];
		philo->id = i + 1;
		philo->alive = true;
		philo->rules = &sim->rules;
		philo->eat_count = 0;
		philo->should_log = &sim->running;
		philo->sim = sim;
		i++;
	}
	return (SUCCESS);
}

static t_status	init_mutexes(t_simulation *sim)
{
	uint16_t	i;
	t_philo		*philo;
	t_fork		*fork;

	sim->forks = malloc(sizeof(t_fork) * sim->philo_count);
	if (sim->forks == NULL)
		return (E_MALLOC_FAILED);
	i = 0;
	while (i < sim->philo_count)
	{
		philo = &sim->philos[i];
		fork = &sim->forks[i];
		pthread_mutex_init(&philo->alive_mutex, NULL);
		pthread_mutex_init(&philo->meal_time_mutex, NULL);
		pthread_mutex_init(&philo->eat_count_mutex, NULL);
		pthread_mutex_init(&fork->mutex, NULL);
		i++;
	}
	pthread_mutex_init(&sim->mutex, NULL);
	assign_forks(sim->philos, sim->forks, sim->philo_count);
	return (SUCCESS);
}

static void	assign_forks(t_philo *philos, t_fork *forks, uint16_t count)
{
	uint16_t	i;
	t_philo		*philo;

	i = 0;
	while (i < count)
	{
		philo = &philos[i];
		if (philo->id == 1)
		{
			philo->left = &forks[count - 1];
			philo->right = &forks[0];
			if (philo->right == philo->left)
				philo->alive = false;
		}
		else
		{
			philo->left = &forks[philo->id - 2];
			philo->right = &forks[philo->id - 1];
		}
		i++;
	}
}
