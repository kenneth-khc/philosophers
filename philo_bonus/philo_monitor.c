/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:38:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/24 21:09:17 by kecheong         ###   ########.fr       */
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
	bool	starved;

	starved = get_current_time() > philo->death_time;
	return (starved);
}

void	kill_philo(t_philo *philo)
{
	philo->alive = false;
}

// void	kill_philos(t_simulation *sim)
// {
// 	t_philo		*philo;
// 	uint16_t	i;
// 	uint16_t	count;

// 	i = 0;
// 	count = sim->philo_count;
// 	while (i < count)
// 	{
// 		philo = &sim->philos[i];
// 		kill_philo(philo);
// 		i++;
// 	}
// }
