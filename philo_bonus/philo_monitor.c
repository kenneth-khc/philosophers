/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:38:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/28 18:59:15 by kecheong         ###   ########.fr       */
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
	if (philo->alive == false)
	{
		sleep_ms(sim->rules.time_to_die);
		log_philo_death(BOLD_RED, sim, philo->id);
	}
	while (philo->alive)
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

/**
 * Original implementation gets current time and compares it with philo's 
 * starvation time. However, TSAN on MacOS detects it as a data race when it 
 * shouldn't be (bug?), it works fine on Linux Ubuntu.
 * Now, mealtime is stored into a timeval struct, and the difference between
 * current time and mealtime is compared with the time to die. This for some
 * reason silences the data race error from TSAN.
 */
bool	philo_starved(t_philo *philo)
{
	bool		starved;
	uint64_t	mealtime;
	uint64_t	time_since_meal;

	sem_wait(philo->mealtime_semaphore);
	mealtime = (
			philo->mealtime.tv_sec * 1000) + (philo->mealtime.tv_usec / 1000);
	time_since_meal = get_current_time() - mealtime;
	starved = time_since_meal > philo->rules->time_to_die;
	sem_post(philo->mealtime_semaphore);
	return (starved);
}
