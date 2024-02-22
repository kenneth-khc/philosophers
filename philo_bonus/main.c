/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/22 09:31:01 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		status = await_philos(&sim);
	if (status == SUCCESS)
		clean_up(&sim);
	handle_errors(status);
	return (status);
}

/* Main thread waits for philos and its monitors to finish running */
t_status	await_philos(t_simulation *sim)
{
	pthread_t	count_checker;
	// t_philo		*philo;
	uint16_t	i;

	if (sim->rules.eat_limit)
	{
		if (pthread_create(&count_checker, NULL, check_count, sim) != 0)
			return (E_THREAD_FAILED);
		if (pthread_join(count_checker, NULL) != 0)
			return (E_JOIN_FAILED);
	}
	i = 0;
	pid_t	dead_philo;
	int		wstatus;
	dead_philo = waitpid(-1, &wstatus, 0);
	sem_wait(sim->master_lock);
	while (i < sim->philo_count)
	{
		kill(sim->pids[i], SIGTERM);
		i++;
	}
	sim->running = false;
	sem_post(sim->master_lock);
	log_message(GREEN, sim, "Simulation ended");
	return (SUCCESS);
}

/* Check each philo's eat count and terminate if all philos satisfied */
void	*check_count(void *arg)
{
	t_simulation	*simulation;
	uint16_t		i;
	uint16_t		philos_satisfied;

	simulation = (t_simulation *)arg;
	philos_satisfied = 0;
	while (philos_satisfied != simulation->philo_count)
	{
		sem_wait(simulation->eat_counter);
		philos_satisfied++;
	}
	// if (i == simulation->philo_count)
	// {
	turn_off_simulation(simulation);
	sem_wait(simulation->master_lock);
	printf("%*u%s All philos ate at least %llu times%s\n", PADDING,
		get_time_since(simulation->start_time), GREEN,
		simulation->rules.required_meals, COLOR_RESET);
	i = 0;
	while (i < simulation->philo_count)
	{
		kill(simulation->pids[i], SIGTERM);
		i++;
	}
	simulation->running = false;
	sem_post(simulation->master_lock);
	// }
	return (NULL);
}

/* Clean up arrays and mutexes */
void	clean_up(t_simulation *simulation)
{
	t_philo		*philo;
	uint16_t	i;

	i = 0;
	while (i < simulation->philo_count)
	{
		philo = &simulation->philos[i];
		i++;
	}
	free(simulation->philos);
}

#define ARG_COUNT_ERR "Invalid number of args\n"
#define USAGE "Usage: <number_of_philosophers> <time_to_die> <time_to_eat>"
#define USAGE2 "<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
#define ARG_TYPE_ERR "Invalid args\nArgs should be positive numbers\n"
#define MALLOC_ERR "Malloc failed\n"
#define THREAD_ERR "Thread failed\n"

/* Print error to stderr according to the given error code */
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
	else
		write(STDERR_FILENO, "Error\n", 6);
	return ;
}
