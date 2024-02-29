/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/29 22:39:23 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	parse_args(argc, argv, &sim);
	init_semaphores(&sim);
	start_simulation(&sim);
	await_philos(&sim);
	clean_up(&sim);
}

/* Clean up arrays and mutexes */
void	clean_up(t_simulation *simulation)
{
	uint16_t	i;

	sem_close(simulation->eat_counter);
	sem_close(simulation->printer);
	sem_close(simulation->forks);
	i = 0;
	while (simulation->mealtime_semaphores[i] != NULL)
	{
		sem_close(simulation->mealtime_semaphores[i]);
		i++;
	}
	free(simulation->mealtime_semaphores);
	free(simulation->pids);
}

#define ARG_COUNT_ERR "Invalid number of args\n"
#define USAGE "Usage: <number_of_philosophers> <time_to_die> <time_to_eat> "
#define USAGE2 "<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
#define ARG_TYPE_ERR "Invalid args\nArgs should be positive numbers\n"
#define MALLOC_ERR "Malloc failed\n"
#define THREAD_ERR "Thread failed\n"
#define JOIN_ERR "Joining thread failed\n"
#define FORK_ERR "Forking processes failed\n"

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

/* Prints error to stderr and terminates the program */
void	error_and_exit(t_status	errcode)
{
	const char	*error_msg;

	if (errcode == E_INVALID_ARG_COUNT)
		error_msg = ARG_COUNT_ERR USAGE USAGE2;
	else if (errcode == E_INVALID_ARG_TYPE)
		error_msg = ARG_TYPE_ERR;
	else if (errcode == E_MALLOC_FAILED)
		error_msg = MALLOC_ERR;
	else if (errcode == E_THREAD_FAILED)
		error_msg = THREAD_ERR;
	else if (errcode == E_JOIN_FAILED)
		error_msg = JOIN_ERR;
	else if (errcode == E_FORK_FAILED)
		error_msg = FORK_ERR;
	else
		error_msg = "Error\n";
	write(STDERR_FILENO, error_msg, strlen(error_msg));
	exit(errcode);
}
