/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:24:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/28 16:41:32 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_philosopher *philos, pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&forks[i], NULL);
		pthread_mutex_init(&philos[i].state_mutex, NULL);
		pthread_mutex_init(&philos[i].alive_mutex, NULL);
		pthread_mutex_init(&philos[i].time_mutex, NULL);
		pthread_mutex_init(&philos[i].eat_count_mutex, NULL);
		i++;
	}
}

void	init_philos(t_philosopher **philos, t_simulation *args)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].alive = true;
		(*philos)[i].state = THINKING;
		(*philos)[i].rules = args->rules;
		(*philos)[i].start_time = args->start_time;
		(*philos)[i].last_meal_time = args->start_time;
		(*philos)[i].eat_count = 0;
		init_hands(&(*philos)[i], args);
		pthread_create(&(*philos)[i].thread, NULL, philosophize, &(*philos)[i]);
		i++;
	}
}

void	init_hands(t_philosopher *philo, t_simulation *sim)
{
	if (philo->id == 1)
	{
		philo->left_fork = &sim->forks[sim->philo_count - 1];
		philo->right_fork = &sim->forks[0];
		if (philo->right_fork == philo->left_fork)
			philo->left_fork = NULL;
	}
	else
	{
		philo->left_fork = &sim->forks[philo->id - 2];
		philo->right_fork = &sim->forks[philo->id - 1];
	}
}
