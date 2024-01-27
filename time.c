/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:50:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/27 10:20:24 by kecheong         ###   ########.fr       */
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
	struct timeval	current_time;
	uint64_t		simulation_time;
	
	gettimeofday(&current_time, NULL);
	simulation_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000 - start_time;
	return (simulation_time);
}


