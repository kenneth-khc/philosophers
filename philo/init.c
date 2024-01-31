/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:24:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/01 07:25:42 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// t_status	init_mutexes1(t_philosopher **philos,
// t_mutex **forks, int count)
// {
// 	int				i;
// 	t_philosopher	*philo;

// 	*forks = malloc(sizeof(**forks) * count);
// 	if (!*forks)
// 		return (E_MALLOC_FAILED);
// 	i = 0;
// 	while (i < count)
// 	{
// 		philo = &(*philos)[i];
// 		pthread_mutex_init(&philo->state_mutex, NULL);
// 		pthread_mutex_init(&philo->alive_mutex, NULL);
// 		pthread_mutex_init(&philo->time_mutex, NULL);
// 		pthread_mutex_init(&philo->eat_count_mutex, NULL);
// 		pthread_mutex_init(&(*forks)[i], NULL);
// 		i++;
// 	}
// 	init_hands(philos, forks, count);
// 	return (SUCCESS);
// }

void	init_hands1(t_philosopher **philos,
t_mutex **forks, uint16_t count)
{//
	int				i;
	t_philosopher	*philo;

	i = 0;
	while (i < count)
	{
		philo = &(*philos)[i];
		if (philo->id == 1)
		{
			philo->left_fork = &(*forks)[count - 1];
			philo->right_fork = &(*forks)[0];
			if (philo->right_fork == philo->left_fork)
				philo->left_fork = NULL;
		}
		else
		{
			philo->left_fork = &(*forks)[philo->id - 2];
			philo->right_fork = &(*forks)[philo->id - 1];
		}
		i++;
	}
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
				// philo->left = NULL;
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
		philo->state = THINKING;
		philo->rules = args->rules;
		philo->start_time = args->start_time;
		philo->last_meal_time = args->start_time;
		philo->eat_count = 0;
		i++;
	}
	return (SUCCESS);
}
