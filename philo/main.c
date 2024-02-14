/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/17 22:33:07 by kecheong         ###   ########.fr       */
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

void	clean_up(t_simulation *simulation)
{
	t_philo		*philo;
	t_fork		*fork;
	uint16_t	i;

	i = 0;
	while (i < simulation->philo_count)
	{
		philo = &simulation->philos[i];
		fork = &simulation->forks[i];
		int errcode;
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

#define ARG_COUNT_ERR "Invalid number of args\n"
#define USAGE "Usage: <number_of_philosophers> <time_to_die> <time_to_eat>"
#define USAGE2 "<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
#define ARG_TYPE_ERR "Invalid args\nArgs should be positive numbers\n"
#define MALLOC_ERR "Malloc failed\n"
#define THREAD_ERR "Thread failed\n"

void	handle_errors(t_status status)
{
	if (status == SUCCESS)
		return ;
	if (status == E_INVALID_ARG_COUNT)
	{
		write(STDERR_FILENO,
			ARG_COUNT_ERR, sizeof(ARG_COUNT_ERR) - 1);
		write(STDERR_FILENO,
			USAGE, sizeof(USAGE) - 1);
		write(STDERR_FILENO,
			USAGE2, sizeof(USAGE2) - 1);
	}
	else if (status == E_INVALID_ARG_TYPE)
		write(STDERR_FILENO,
			ARG_TYPE_ERR, sizeof(ARG_TYPE_ERR) - 1);
	else if (status == E_MALLOC_FAILED)
		write(STDERR_FILENO,
			MALLOC_ERR, sizeof(MALLOC_ERR) - 1);
	else if (status == E_THREAD_FAILED)
		write(STDERR_FILENO,
			THREAD_ERR, sizeof(THREAD_ERR) - 1);
	return ;
}
