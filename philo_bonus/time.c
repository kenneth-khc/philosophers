/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:50:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/22 00:08:48 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Returns the current time since Epoch in milliseconds */
uint64_t	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

/* Returns the amount of milliseconds elapsed since a timestamp */
uint32_t	get_time_since(uint64_t start_time)
{
	struct timeval	current_time;
	uint32_t		elapsed_ms;

	gettimeofday(&current_time, NULL);
	elapsed_ms
		= (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)
		- start_time;
	return (elapsed_ms);
}

/* Sleeps for around "ms_to_sleep" milliseconds */
void	sleep_ms(uint64_t ms_to_sleep)
{
	uint64_t	start_time;
	uint64_t	time_spent_sleeping;

	start_time = get_current_time();
	time_spent_sleeping = 0;
	while (time_spent_sleeping < ms_to_sleep)
	{
		usleep(650);
		time_spent_sleeping = get_time_since(start_time);
	}
	return ;
}
