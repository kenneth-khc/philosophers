/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:14:02 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/02 20:03:20 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophize(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)(arg);
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

void	pick_up_fork(t_philosopher *philo, t_fork *fork)
{
	if (!philo_is_alive(philo))
		return ;
	pthread_mutex_lock(&fork->mutex);
	color_printf(BLUE,
		get_time_since(philo->start_time), philo->id, "has taken a fork");
}

void	philo_eating(t_philosopher *philo)
{
	if (!philo_is_alive(philo))
		return ;
	uint64_t	time_1 = get_current_time();
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_current_time();
	if (time_1 != philo->last_meal_time)
		printf("nope\n");
	pthread_mutex_unlock(&philo->meal_time_mutex);
	color_printf(MAGENTA,
		get_time_since(philo->start_time), philo->id, "is eating");
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	ft_usleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
}

void	philo_sleeping(t_philosopher *philo)
{
	if (!philo_is_alive(philo))
		return ;
	color_printf(CYAN,
		get_time_since(philo->start_time), philo->id, "is sleeping");
	ft_usleep(philo->rules->time_to_sleep);
}

void	philo_thinking(t_philosopher *philo)
{
	if (!philo_is_alive(philo))
		return ;
	color_printf(YELLOW,
		get_time_since(philo->start_time), philo->id, "is thinking");
}
