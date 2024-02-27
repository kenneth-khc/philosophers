/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:38:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/27 19:33:43 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* A secondary thread to monitor whether it's philo has starved or not */
void	*philo_monitor(void	*arg)
{
	t_philo			*philo;
	t_simulation	*sim;

	philo = (t_philo *)arg;
	sim = philo->simulation;
	if (philo_is_alive(philo) == false)
	{
		sleep_ms(sim->rules.time_to_die);
		log_philo_death(BOLD_RED, sim, philo->id);
	}
	while (philo_is_alive(philo))
	{
		sleep_ms(1);
		if (philo_starved(philo))
		{
			log_philo_death(BOLD_RED, sim, philo->id);
			exit(EXIT_SUCCESS);
		}
	}
	return (NULL);
}

/* Get current time and compare it with philo's starvation time */
bool	philo_starved(t_philo *philo)
{
	bool		starved;
	uint64_t	meal_time;
	uint64_t	time_since_meal;
	
	sem_wait(philo->death_semaphore);
	meal_time = (philo->meal_tv.tv_sec * 1000) + (philo->meal_tv.tv_usec / 1000);
	time_since_meal = get_current_time() - meal_time;
	starved = time_since_meal > philo->rules->time_to_die;
	sem_post(philo->death_semaphore);
	return (starved);
}
