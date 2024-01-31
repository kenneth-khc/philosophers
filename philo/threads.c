/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:14:02 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/01 07:33:13 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_down_forks(t_philosopher *philo);

void	*philosophize(void *arg)
{
	t_philosopher	*philo;
	bool			left_hand;
	bool			right_hand;

	philo = (t_philosopher *)(arg);
	if (philo->id % 2 == 0)
		usleep(50);
	left_hand = false;
	right_hand = false;
	while (philo_is_alive(philo))
	{
		// while (!left_hand || !right_hand)
		// {
			// put_down_forks(philo);
			left_hand = pick_up_fork(philo, philo->left);
			right_hand = pick_up_fork(philo, philo->right);
		// }
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	// while (philo_is_alive(philo))
	// {
	// 	if (philo->state == THINKING)
	// 	{
	// 		// if (philo_can_eat(philo->left, philo->right))
	// 		// {
				
	// 		left_hand = pick_up_fork(philo, philo->left);
	// 		// if (left_hand)
	// 			right_hand = pick_up_fork(philo, philo->right);
	// 		// if (left_hand && right_hand)
	// 			philo_eating(philo);
			
	// 	}
	// 	else if (philo->state == EATING)
	// 		philo_sleeping(philo);
	// 	else if (philo->state == SLEEPING)
	// 		philo_thinking(philo);
	// }
	return (NULL);
}

bool	philo_can_eat(t_fork *left_fork, t_fork *right_fork)
{
	bool	left_free;
	bool	right_free;

	left_free = false;
	right_free = false;
	pthread_mutex_lock(&left_fork->picked_up_mutex);
	pthread_mutex_lock(&right_fork->picked_up_mutex);
	left_free = left_fork->is_picked_up == false;
	right_free = right_fork->is_picked_up == false;
	pthread_mutex_unlock(&left_fork->picked_up_mutex);
	pthread_mutex_unlock(&right_fork->picked_up_mutex);
	return (left_free && right_free);
}

bool	pick_up_fork(t_philosopher *philo, t_fork *fork)
{
	if (fork == NULL)
		return (false);
	pthread_mutex_lock(&fork->mutex);
	// pthread_mutex_lock(&fork->picked_up_mutex);
	if (fork->is_picked_up)
	{
		// pthread_mutex_unlock(&fork->picked_up_mutex);
		return (false);
	}
	if (fork->is_picked_up == false)
		fork->is_picked_up = true;
	// pthread_mutex_unlock(&fork->picked_up_mutex);
	if (philo_is_alive(philo))
		color_printf(BLUE,
			get_time_since(philo->start_time), philo->id, "has taken a fork");
	return (true);
}

void	philo_eating(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->time_mutex);
	if (philo_is_alive(philo))
		color_printf(MAGENTA,
			get_time_since(philo->start_time), philo->id, "is eating");
	philo->state = EATING;
	ft_usleep(philo->rules.time_to_eat);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	philo->left->is_picked_up = false;
	philo->right->is_picked_up = false;
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
}

void	philo_sleeping(t_philosopher *philo)
{
	if (philo_is_alive(philo))
		color_printf(CYAN,
			get_time_since(philo->start_time), philo->id, "is sleeping");
	philo->state = SLEEPING;
	ft_usleep(philo->rules.time_to_sleep);
}

void	philo_thinking(t_philosopher *philo)
{
	philo->state = THINKING;
	if (philo_is_alive(philo))
	{
		color_printf(YELLOW,
			get_time_since(philo->start_time), philo->id, "is thinking");
	}
}
