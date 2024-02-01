/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:24:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/01 08:51:06 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status	init_philos(t_philosopher **philos, t_simulation *args)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	*philos = malloc(sizeof(**philos) * args->philo_count);
	if (!*philos)
		return (E_MALLOC_FAILED);
	while (i < args->philo_count)
	{
		philo = &(*philos)[i];
		philo->id = i + 1;
		philo->alive = true;
		philo->rules = &args->rules;
		philo->start_time = args->start_time;
		philo->last_meal_time = args->start_time;
		philo->eat_count = 0;
		i++;
	}
	return (SUCCESS);
}

t_status	init_muts(t_simulation *sim,
	t_philosopher **philos, uint16_t philo_count)
{
	uint16_t		i;
	t_philosopher	*philo;

	sim->fork_arr = malloc(sizeof(t_fork) * philo_count);
	if (!sim->fork_arr)
		return (E_MALLOC_FAILED);
	i = 0;
	while (i < philo_count)
	{
		philo = &(*philos)[i];
		pthread_mutex_init(&philo->alive_mutex, NULL);
		pthread_mutex_init(&philo->meal_time_mutex, NULL);
		pthread_mutex_init(&philo->eat_count_mutex, NULL);
		pthread_mutex_init(&sim->fork_arr[i].mutex, NULL);
		i++;
	}
	init_hands(philos, sim->fork_arr, philo_count);
	return (SUCCESS);
}

void	init_hands(t_philosopher **philos, t_fork *forks, uint16_t count)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	while (i < count)
	{
		philo = &(*philos)[i];
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
