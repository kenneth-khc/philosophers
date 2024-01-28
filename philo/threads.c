/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:14:02 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/28 16:56:16 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophize(void *arg)
{
	t_philosopher	*philo;
	bool			left_hand;
	bool			right_hand;

	philo = (t_philosopher *)(arg);
	left_hand = false;
	right_hand = false;
	while (philo_is_alive(philo))
	{
		if (philo->state == THINKING)
		{
			left_hand = pick_up_left_fork(philo);
			if (left_hand)
				right_hand = pick_up_right_fork(philo);
			if (left_hand && right_hand)
				philo_eating(philo);
		}
		else if (philo->state == EATING)
		{
			philo_sleeping(philo);
		}
		else if (philo->state == SLEEPING)
		{
			philo_thinking(philo);
		}
	}
	return (NULL);
}

bool	pick_up_left_fork(t_philosopher *philo)
{
	if (philo->left_fork == NULL)
		return (false);
	pthread_mutex_lock(philo->left_fork);
	if (philo_is_alive(philo))
		printf(BLU"%.10llu %d has taken a fork\n"COLOR_RESET,
			get_time_since(philo->start_time), philo->id);
	// color_printf(BLU, philo->start_time, philo->id, "has taken a fork\n");
	return (true);
}

bool	pick_up_right_fork(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (philo_is_alive(philo))
		printf(BLU"%.10llu %d has taken a fork\n"COLOR_RESET,
			get_time_since(philo->start_time), philo->id);
	// color_printf(BLU, philo->start_time, philo->id, "has taken a fork\n");
	return (true);
}

void	philo_eating(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->time_mutex);
	if (philo_is_alive(philo))
		printf(MAG"%.10llu %d is eating\n"COLOR_RESET,
			get_time_since(philo->start_time), philo->id);
	// color_printf(MAG, philo->start_time, philo->id, "is eating\n");
	philo->state = EATING;
	sleep_millisecond(philo->rules.time_to_eat);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleeping(t_philosopher *philo)
{
	if (philo_is_alive(philo))
		printf(CYN"%.10llu %d is sleeping\n"COLOR_RESET,
			get_time_since(philo->start_time), philo->id);
	// color_printf(CYN, philo->start_time, philo->id, "is sleeping\n");
	philo->state = SLEEPING;
	sleep_millisecond(philo->rules.time_to_sleep);
}

void	philo_thinking(t_philosopher *philo)
{
	philo->state = THINKING;
	if (philo_is_alive(philo))
		printf(YEL"%.10llu %d is thinking\n"COLOR_RESET,
			get_time_since(philo->start_time), philo->id);
	// color_printf(YEL, philo->start_time, philo->id, "is thinking\n");
}

bool	philo_is_alive(t_philosopher *philo)
{
	bool	alive;

	pthread_mutex_lock(&philo->alive_mutex);
	alive = philo->alive;
	pthread_mutex_unlock(&philo->alive_mutex);
	return (alive);
}
