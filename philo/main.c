/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/29 22:47:56 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
	t_status		status;

	status = parse_args(argc, argv, &sim);
	if (status == SUCCESS)
		status = init_simulation(&sim);
	if (status == SUCCESS)
		status = start_simulation(&sim);
	if (status == SUCCESS)
		status = await_philos(&sim);
	if (status == SUCCESS)
		clean_up(&sim);
	handle_errors(status);
	return (status);
}

/* Clean up arrays and mutexes */
void	clean_up(t_simulation *simulation)
{
	t_philo		*philo;
	t_fork		*fork;
	uint16_t	i;

	i = 0;
	while (i < simulation->philo_count)
	{
		philo = &simulation->philos[i];
		pthread_mutex_destroy(&philo->alive_mutex);
		pthread_mutex_destroy(&philo->eat_count_mutex);
		fork = &simulation->forks[i];
		pthread_mutex_destroy(&fork->mutex);
		i++;
	}
	free(simulation->philos);
	free(simulation->forks);
	pthread_mutex_destroy(&simulation->mutex);
}

static size_t	strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

#define ARG_COUNT_ERR "Invalid number of args\n"
#define USAGE "Usage: <number_of_philosophers> <time_to_die> <time_to_eat> "
#define USAGE2 "<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
#define ARG_TYPE_ERR "Invalid args\nArgs should be positive numbers\n"
#define MALLOC_ERR "Malloc failed\n"
#define THREAD_ERR "Thread failed\n"

/* Print error to stderr according to the given error code */
void	handle_errors(t_status status)
{
	const char	*error_msg;

	if (status == SUCCESS)
		return ;
	if (status == E_INVALID_ARG_COUNT)
		error_msg = ARG_COUNT_ERR USAGE USAGE2;
	else if (status == E_INVALID_ARG_TYPE)
		error_msg = ARG_TYPE_ERR;
	else if (status == E_MALLOC_FAILED)
		error_msg = MALLOC_ERR;
	else if (status == E_THREAD_FAILED)
		error_msg = THREAD_ERR;
	else
		error_msg = "Error\n";
	write(STDERR_FILENO, error_msg, strlen(error_msg));
}
