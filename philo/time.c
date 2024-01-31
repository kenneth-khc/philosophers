/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:50:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/01 07:33:55 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

uint64_t	get_time_since(uint64_t start_time)
{
	struct timeval	current_time;
	uint64_t		elapsed_ms;

	gettimeofday(&current_time, NULL);
	elapsed_ms
		= current_time.tv_sec * 1000 + current_time.tv_usec / 1000 - start_time;
	return (elapsed_ms);
}

void	ft_usleep(uint64_t milliseconds_to_sleep)
{
	uint64_t	start_time;
	uint64_t	time_spent_sleeping;

	start_time = get_current_time();
	time_spent_sleeping = 0;
	while (time_spent_sleeping < milliseconds_to_sleep)
	{
		usleep(50);
		time_spent_sleeping = get_time_since(start_time);
	}
	return ;
}
