/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:21:37 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/25 22:22:13 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_philo(t_simulation *sim);

/* Create threads to run each philosopher's routine */
void	start_simulation(t_simulation *sim)
{
	uint16_t	i;
	pid_t		id;

	i = 0;
	sim->start_time = get_current_time();
	sim->pids = malloc(sizeof(pid_t) * sim->philo_count);
	//
	init_philo(sim);
	while (i < sim->philo_count)
	{
		sim->p.id = i + 1;
		sim->p.death_sema = sim->philo_semas[i];
		id = fork();
		if (id == -1)
			exit(EXIT_FAILURE);
		else if (id == 0)
		{
			philosophize(&sim->p);
		}
		else
			sim->pids[i] = id;
		// printf("Spawned %d\n", sim->pids[i]);
		i++;
	}
}

static void	init_philo(t_simulation *sim)
{
	t_philo	*philo;

	philo = &sim->p;
	philo->simulation = sim;
	philo->rules = &sim->rules;
	philo->eat_count = 0;
	sim->start_time = get_current_time();
	philo->last_meal_time = sim->start_time;
	philo->death_time = philo->last_meal_time + sim->rules.time_to_die;
	if (sim->philo_count > 1)
		philo->alive = true;
	else
		philo->alive = false;
}

/* Log general simulation messages */
void	log_message(const char *color, t_simulation *sim, const char *msg)
{
	uint32_t	timestamp;

	// sem_wait(sim->printer);
	timestamp = get_time_since(sim->start_time);
	printf("%*u%s %s%s\n", PADDING,
		timestamp, color, msg, COLOR_RESET);
	// sem_post(sim->printer);
}

/* Log a philo's action */
void	log_philo_action(const char *color, t_philo *philo, const char *msg)
{
	t_simulation	*sim;
	uint32_t		timestamp;

	sim = philo->simulation;
	// if (simulation_is_running(sim) && philo_is_alive(philo))
	// {
		sem_wait(sim->printer);
		timestamp = get_time_since(sim->start_time);
		printf("%*u%s %d %s%s\n", PADDING,
			timestamp, color, philo->id, msg, COLOR_RESET);
		sem_post(sim->printer);
	// }
}

/* Log a philo's death */
void	log_philo_death(const char *color, t_simulation *sim, uint16_t id)
{
	uint32_t	timestamp;

	// if (simulation_is_running(sim))
	// {
		sem_wait(sim->printer);
		// turn_off_simulation(sim);
		timestamp = get_time_since(sim->start_time);
		printf("%*u%s %d %s%s\n", PADDING,
			timestamp, color, id, "died", COLOR_RESET);
		// sem_post(sim->printer);
	// }
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