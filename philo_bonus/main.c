/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/28 22:21:10 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	// set_sigterm_handler();
	parse_args(argc, argv, &sim);
	init_semaphores(&sim);
	start_simulation(&sim);
	await_philos(&sim);
	clean_up(&sim);
}

	// int	ret;
/* Main thread waits for philos and its monitors to finish running */
void	await_philos(t_simulation *sim)
{
	// pthread_t	count_checker;
	uint16_t	i;
	pid_t		id = 0;

	// if (sim->rules.eat_limit)
	// {
	// 	if (pthread_create(&count_checker, NULL, check_count, sim) != 0)
	// 		error_and_exit(E_THREAD_FAILED);
	// 	pthread_detach(count_checker);
	// }
	if (sim->rules.eat_limit)
	{
		id = fork();
		if (id == -1)
			exit(EXIT_FAILURE);
		else if (id == 0)
			check_count(sim);
	}
	i = 0;
	waitpid(-1, NULL, 0);
	if (sim->rules.eat_limit)
		kill(id, SIGTERM);
	while (i < sim->philo_count)
	{
		kill(sim->pids[i], SIGTERM);
		i++;
	}
	log_message(GREEN, sim, "Simulation ended");
}

/* Check each philo's eat count and terminate if all philos satisfied */
void	*check_count(void *arg)
{
	t_simulation	*sim;
	uint16_t		philos_satisfied;

	sim = (t_simulation *)arg;
	philos_satisfied = 0;
	// pid_t	dead = 0;
	while (philos_satisfied < sim->philo_count)
	{
		sem_wait(sim->eat_counter);
		philos_satisfied++;
	}
	sem_wait(sim->printer);
	printf("%*u%s All philos ate at least %llu times%s\n", PADDING,
		get_time_since(sim->start_time), GREEN,
		sim->rules.required_meals, COLOR_RESET);
	// return (NULL);
	exit(EXIT_SUCCESS);
}

/* Clean up arrays and mutexes */
void	clean_up(t_simulation *simulation)
{
	uint16_t	i;

	sem_close(simulation->eat_counter);
	sem_close(simulation->printer);
	sem_close(simulation->forks);
	i = 0;
	while (simulation->philo_semaphores[i] != NULL)
	{
		sem_close(simulation->philo_semaphores[i]);
		i++;
	}
	free(simulation->philo_semaphores);
	free(simulation->pids);
}

#define ARG_COUNT_ERR "Invalid number of args\n"
#define USAGE "Usage: <number_of_philosophers> <time_to_die> <time_to_eat>"
#define USAGE2 "<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
#define ARG_TYPE_ERR "Invalid args\nArgs should be positive numbers\n"
#define MALLOC_ERR "Malloc failed\n"
#define THREAD_ERR "Thread failed\n"

/* Prints error to stderr and terminates the program */
void	error_and_exit(t_status	errcode)
{
	if (errcode == E_INVALID_ARG_COUNT)
	{
		write(STDERR_FILENO,
			ARG_COUNT_ERR, sizeof(ARG_COUNT_ERR) - 1);
		write(STDERR_FILENO,
			USAGE, sizeof(USAGE) - 1);
		write(STDERR_FILENO,
			USAGE2, sizeof(USAGE2) - 1);
	}
	else if (errcode == E_INVALID_ARG_TYPE)
		write(STDERR_FILENO,
			ARG_TYPE_ERR, sizeof(ARG_TYPE_ERR) - 1);
	else if (errcode == E_MALLOC_FAILED)
		write(STDERR_FILENO,
			MALLOC_ERR, sizeof(MALLOC_ERR) - 1);
	else if (errcode == E_THREAD_FAILED)
		write(STDERR_FILENO,
			THREAD_ERR, sizeof(THREAD_ERR) - 1);
	else
		write(STDERR_FILENO, "Error\n", 6);
	exit(errcode);
}
