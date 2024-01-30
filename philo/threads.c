/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:14:02 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/29 23:19:51 by kecheong         ###   ########.fr       */
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
			philo_sleeping(philo);
		else if (philo->state == SLEEPING)
			philo_thinking(philo);
	}
	return (NULL);
}

bool	pick_up_left_fork(t_philosopher *philo)
{
	if (philo->left_fork == NULL)
		return (false);
	pthread_mutex_lock(philo->left_fork);
	if (philo_is_alive(philo))
		color_printf(BLUE, philo->start_time, philo->id, "has taken a fork");
	return (true);
}

bool	pick_up_right_fork(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (philo_is_alive(philo))
		color_printf(BLUE, philo->start_time, philo->id, "has taken a fork");
	return (true);
}

void	philo_eating(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->time_mutex);
	if (philo_is_alive(philo))
		color_printf(MAGENTA, philo->start_time, philo->id, "is eating");
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
		color_printf(CYAN, philo->start_time, philo->id, "is sleeping");
	philo->state = SLEEPING;
	sleep_millisecond(philo->rules.time_to_sleep);
}

void	philo_thinking(t_philosopher *philo)
{
	philo->state = THINKING;
	if (philo_is_alive(philo))
		color_printf(YELLOW, philo->start_time, philo->id, "is thinking");
}
