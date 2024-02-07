/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/08 00:06:53 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
	t_status		status;

	status = parse_args(argc, argv, &sim);
	if (status == SUCCESS)
		status = initialize_simulation(&sim);
	if (status == SUCCESS)
		status = start_simulation(&sim);
	if (status == SUCCESS)
		status = monitor_philos(&sim);
	if (status == SUCCESS)
		clean_up(&sim);
	handle_errors(status);
	// system("leaks -q philo");
	return (status);
}

t_status	start_simulation(t_simulation *simulation)
{
	uint16_t	i;
	t_philo		*philos;

	i = 0;
	philos = simulation->philos;
	simulation->running = false;
	while (i < simulation->philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philosophize, &philos[i]) != 0)
			return (E_THREAD_FAILED);
		// pthread_detach(philos[i].thread);
		i++;
	}
	pthread_mutex_lock(&simulation->mutex);
	simulation->running = true;
	simulation->start_time = get_current_time();
	i = 0;
	while (i < simulation->philo_count)
	{
		simulation->philos[i].start_time = simulation->start_time;
		simulation->philos[i].last_meal_time = simulation->start_time;
		i++;
	}
	log_message(GREEN,
		get_time_since(simulation->start_time), NULL, "Simulation started");
	pthread_mutex_unlock(&simulation->mutex);
	return (SUCCESS);
}

void	clean_up(t_simulation *simulation)
{
	uint16_t	i;
	t_philo		*philo;
	t_fork		*fork;

	i = 0;
	int errcode;
	// pthread_mutex_unlock(&simulation->philos[0].right->mutex);
	// pthread_mutex_unlock(&simulation->philos[2].right->mutex);
	while (i < simulation->philo_count)
	{
		philo = &simulation->philos[i];
		fork = &simulation->forks[i];
		// if (pthread_mutex_destroy(&philo->alive_mutex) != 0)
		// 	printf("MUTEX1 %d\n", i);
		// if (pthread_mutex_destroy(&philo->meal_time_mutex) != 0)
		// 	printf("MUTEX2 %d\n", i);
		// if (pthread_mutex_destroy(&philo->eat_count_mutex) != 0)
		// 	printf("MUTEX3 %d\n", i);
		// if (pthread_mutex_destroy(&fork->mutex) != 0)
		// 	printf("MUTEX4 %d\n", i);
		if ((errcode = pthread_mutex_destroy(&philo->alive_mutex)) != 0)
			printf("MUTEX1 %d Errcode: %d\n", i, errcode);
		if ((errcode = pthread_mutex_destroy(&philo->meal_time_mutex)) != 0)
			printf("MUTEX2 %d Errcode: %d\n", i, errcode);
		if ((errcode = pthread_mutex_destroy(&philo->eat_count_mutex)) != 0)
			printf("MUTEX3 %d Errcode: %d\n", i, errcode);
		if ((errcode = pthread_mutex_destroy(&fork->mutex)) != 0)
			printf("MUTEX4 %d Errcode: %d\n", i, errcode);
		i++;
	}
	free(simulation->philos);
	free(simulation->forks);
	pthread_mutex_destroy(&simulation->mutex);
}
