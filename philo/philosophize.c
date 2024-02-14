/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:14:02 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/17 23:54:07 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophize(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)(arg);
	pthread_mutex_lock(&philo->simulation->mutex);
	pthread_mutex_unlock(&philo->simulation->mutex);
	if (philo->left_fork == philo->right_fork)
	{
		sleep_ms(philo->rules->time_to_die);
		philo->alive = false;
		// log_philo_death(RED, philo->simulation, philo->id);
	}
	if (philo->id % 2 == 0)
		sleep_ms(1);
	while (philo_is_alive(philo))
	{
		pick_up_fork(philo, philo->left_fork);
		pick_up_fork(philo, philo->right_fork);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	log_philo_death(RED, philo->simulation, philo->id);
	return (NULL);
}

int	pick_up_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	log_philo_action(BLUE, philo, "has taken a fork");
	return (1);
}

void	philo_eating(t_philo *philo)
{
	uint64_t	meal_start_time;
	uint64_t	meal_end_time;

	meal_start_time = get_current_time();
	philo->last_meal_time = meal_start_time;
	meal_end_time = meal_start_time + philo->rules->time_to_eat;
	philo->death_time = meal_start_time + philo->rules->time_to_die;
	log_philo_action(MAGENTA, philo, "is eating");
	if (meal_end_time < philo->death_time)
	{
		sleep_ms(philo->rules->time_to_eat);
		pthread_mutex_lock(&philo->eat_count_mutex);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->eat_count_mutex);
	}
	else
	{
		sleep_to_death(philo, philo->simulation, meal_start_time);
	}
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	philo_sleeping(t_philo *philo)
{
	uint64_t	curr_time;
	uint64_t	wake_time;

	curr_time = get_current_time();
	wake_time = curr_time + philo->rules->time_to_sleep;
	log_philo_action(CYAN, philo, "is sleeping");
	if (wake_time < philo->death_time)
		sleep_ms(philo->rules->time_to_sleep);
	else
	{
		sleep_to_death(philo, philo->simulation, curr_time);
	}
}

void	sleep_to_death(t_philo *philo, t_simulation *sim, uint64_t start_time)
{
	sleep_ms(philo->death_time - start_time);
	pthread_mutex_lock(&sim->mutex);
	kill_philos(philo, sim->philos, sim->philo_count);
	pthread_mutex_unlock(&sim->mutex);
}

void	philo_thinking(t_philo *philo)
{
	log_philo_action(YELLOW, philo, "is thinking");
}
