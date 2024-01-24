/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:03:56 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/24 21:03:03 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_left_fork(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_hand);
	printf(BLK"%.10u %d has taken a fork\n"COLOR_RESET, 
		get_program_time(philo->start_time), philo->id);
	// pthread_mutex_unlock(philo->left_hand);
}

void	pick_up_right_fork(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_hand);
	printf(BLK"%.10u %d has taken a fork\n"COLOR_RESET, 
		get_program_time(philo->start_time), philo->id);
	// pthread_mutex_unlock(philo->right_hand);
}

void	munch_munch(t_philosopher *philo)
{
	philo->last_meal_time = get_program_time(philo->start_time);
	printf(MAG"%.10u %d is eating\n"COLOR_RESET,
		philo->last_meal_time, philo->id);
	philo->state = EATING;
	sleep_millisecond(philo->rules.time_to_eat);
	pthread_mutex_unlock(philo->left_hand);
	pthread_mutex_unlock(philo->right_hand);
}

void	philo_sleeping(t_philosopher *philo)
{
	printf(CYN"%.10u %d is sleeping\n"COLOR_RESET,
		get_program_time(philo->start_time), philo->id);
	philo->state = SLEEPING;
	sleep_millisecond(philo->rules.time_to_sleep);
	philo->state = THINKING;
	printf(YEL"%.10u %d is thinking\n"COLOR_RESET,
		get_program_time(philo->start_time), philo->id);
}

bool	philo_is_alive(t_philosopher *philo)
{
	// uint32_t	current_time;
	// current_time = get_program_time(philo->start_time);
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec < philo->last_meal_time + philo->rules.time_to_die);
}