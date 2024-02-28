/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:21:37 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/28 19:00:48 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_philo(t_simulation *sim);

/* Create threads to run each philosopher's routine */
void	start_simulation(t_simulation *sim)
{
	uint16_t	i;

	sim->pids = malloc(sizeof(pid_t) * sim->philo_count);
	if (sim->pids == NULL)
		error_and_exit(E_MALLOC_FAILED);
	init_philo(sim);
	fork_philos(sim);
	i = 0;
	while (i <= sim->philo_count)
	{
		i++;
	}
}

void	fork_philos(t_simulation *sim)
{
	pid_t		id;
	uint16_t	i;

	i = 0;
	uint16_t	j = 0;
	while (i < sim->philo_count)
	{
		// j = 0;
		// while (j < 10 && i + j < sim->philo_count)
		// {
			sim->philo.id = i + j + 1;
			// sim->philo.mealtime_semaphore = sim->mealtime_semaphores[i+j];
			id = fork();
			if (id == -1)
				exit(EXIT_FAILURE);
			else if (id == 0)
				philosophize(&sim->philo);
			else
				sim->pids[i+j] = id;
			// j++;
		// }
		// sleep_ms(1);
		// i += 10;
		i++;
	}
}

static void	init_philo(t_simulation *sim)
{
	t_philo	*philo;

	philo = &sim->philo;
	philo->simulation = sim;
	philo->rules = &sim->rules;
	philo->eat_count = 0;
	if (sim->philo_count > 1)
		philo->alive = true;
	else
		philo->alive = false;
	sim->running = true;
	sim->start_time = get_current_time();
	philo->last_meal_time = sim->start_time;
	philo->death_time = philo->last_meal_time + sim->rules.time_to_die;
}

/* Log general simulation messages */
void	log_message(const char *color, t_simulation *sim, const char *msg)
{
	uint32_t	timestamp;

	timestamp = get_time_since(sim->start_time);
	printf("%*u%s %s%s\n", PADDING,
		timestamp, color, msg, COLOR_RESET);
}

/* Log a philo's action */
void	log_philo_action(const char *color, t_philo *philo, const char *msg)
{
	t_simulation	*sim;
	uint32_t		timestamp;

	sim = philo->simulation;
	sem_wait(sim->printer);
	timestamp = get_time_since(sim->start_time);
	printf("%*u%s %d %s%s\n", PADDING,
		timestamp, color, philo->id, msg, COLOR_RESET);
	sem_post(sim->printer);
}

/* Log a philo's death */
void	log_philo_death(const char *color, t_simulation *sim, uint16_t id)
{
	uint32_t	timestamp;

	sem_wait(sim->printer);
	timestamp = get_time_since(sim->start_time);
	printf("%*u%s %d %s%s\n", PADDING,
		timestamp, color, id, "died", COLOR_RESET);
}

/* Starts the simulation once all threads are successfully created */
// static void	unpause_threads(t_simulation *sim)
// {
// 	t_philo		*philo;
// 	uint16_t	i;

// 	sim->running = true;
// 	sim->start_time = get_current_time();
// 	i = 0;
// 	while (i < sim->philo_count)
// 	{
// 		philo = &sim->philos[i];
// 		philo->last_meal_time = sim->start_time;
// 		philo->death_time = philo->last_meal_time + philo->rules->time_to_die;
// 		i++;
// 	}
// 	log_message(GREEN, sim, "Simulation started");
// }