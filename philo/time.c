/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:50:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/28 16:58:53 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_millisecond(uint64_t milliseconds)
{
	unsigned int	microseconds;

	microseconds = milliseconds * 1000;
	usleep(microseconds);
}

uint64_t	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

uint64_t	get_time_since(uint64_t start_time)
{
	struct timeval	time_now;
	uint64_t		elapsed_ms;

	gettimeofday(&time_now, NULL);
	elapsed_ms
		= time_now.tv_sec * 1000 + time_now.tv_usec / 1000 - start_time;
	return (elapsed_ms);
}
