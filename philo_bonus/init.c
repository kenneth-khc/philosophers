/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:24:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/24 22:13:11 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static void
// init_philos(t_simulation *sim);

// static void
// init_semaphores(t_simulation *sim);

/* Initialize the simulation to be run but keep the threads paused */
// void	init_simulation(t_simulation *sim)
// {
// 	// sim->running = true;
// 	init_philos(sim);
// 	init_semaphores(sim);
// }

// /* Initializes philos and sets their id and state to alive */
// static void	init_philos(t_simulation *sim)
// {
// 	t_philo		*philo;
// 	uint16_t	i;

// 	sim->philos = malloc(sizeof(t_philo) * sim->philo_count);
// 	if (sim->philos == NULL)
// 		error_and_exit(E_MALLOC_FAILED);
// 	i = 0;
// 	while (i < sim->philo_count)
// 	{
// 		philo = &sim->philos[i];
// 		philo->simulation = sim;
// 		philo->rules = &sim->rules;
// 		philo->id = i + 1;
// 		philo->alive = true;
// 		philo->eat_count = 0;
// 		i++;
// 	}
// 	if (sim->philo_count == 1)
// 		philo->alive = false;
// }

// static void init_semaphores(t_simulation *sim)
void init_semaphores(t_simulation *sim)
{
	(void)sim;
	sem_unlink("FORKS");
	sim->forks = sem_open("FORKS", O_CREAT, 0666, sim->philo_count);
	sem_unlink("MASTER");
	sim->master_lock = sem_open("MASTER", O_CREAT, 0666, 1);
	sem_unlink("PRINTER");
	sim->printer = sem_open("PRINTER", O_CREAT, 0666, 1);
	sem_unlink("EAT_COUNTER");
	sim->eat_counter = sem_open("EAT_COUNTER", O_CREAT, 0666, 0);
	sem_unlink("TERMINATOR");
	sim->terminator = sem_open("TERMINATOR", O_CREAT, 0666, 0);
	sim->philo_semas = malloc((sizeof(sem_t *) * sim->philo_count));
	if (sim->philo_semas == NULL)
		error_and_exit(E_MALLOC_FAILED);
	
	uint16_t	i;
	char		name[17];
	i = 0;
	while (i < sim->philo_count)
	{
		i++;
		generate_semaphore_name(name, i);
		log("Name: %s\n", name);
	}
	exit(0);
}

void	generate_semaphore_name(char *name, uint16_t num)
{
	int		i;

	i = 4;
	const char	digits[] = "0123456789abcdef";
	
	name[i] = '\0';
	while (i > 0)
	{
		i--;
		name[i] = digits[num & 0xF];
		num >>= 4;
	}
	
}
