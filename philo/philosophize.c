/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:14:02 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/08 00:10:20 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophize(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)(arg);
	while (simulation_is_running(philo->sim) == false)
	{
		;
	}
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (philo_is_alive(philo))
	{
		pick_up_fork(philo, philo->left);
		pick_up_fork(philo, philo->right);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}

void	pick_up_fork(t_philo *philo, t_fork *fork)
{
	if (!philo_is_alive(philo))
		return ;
	pthread_mutex_lock(&fork->mutex);
	log_message(BLUE,
		get_time_since(philo->start_time), philo, "has taken a fork");
}

void	philo_eating(t_philo *philo)
{
	uint64_t	meal_time;

	if (!philo_is_alive(philo))
		return ;
	meal_time = get_current_time();
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = meal_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	log_message(MAGENTA,
		get_time_since(philo->start_time), philo, "is eating");
	ft_usleep(philo->rules->time_to_eat);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
}

void	philo_sleeping(t_philo *philo)
{
	if (!philo_is_alive(philo))
		return ;
	log_message(CYAN,
		get_time_since(philo->start_time), philo, "is sleeping");
	ft_usleep(philo->rules->time_to_sleep);
}

void	philo_thinking(t_philo *philo)
{
	if (!philo_is_alive(philo))
		return ;
	log_message(YELLOW,
		get_time_since(philo->start_time), philo, "is thinking");
}
