/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:50:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/24 20:53:12 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_seconds(unsigned int seconds)
{
	unsigned int	microseconds;

	microseconds = seconds * 1000000;
	printf("Sleeping for %d seconds / ", seconds);
	printf("%d milliseconds / ", seconds * 1000);
	printf("%d microseconds\n", microseconds);
	usleep(microseconds);
}

void	sleep_millisecond(unsigned int milliseconds)
{
	unsigned int	microseconds;

	microseconds = milliseconds * 100;
	// printf("Sleeping for %.1f seconds / ", milliseconds / 1000.0);
	// printf("%d milliseconds / ", milliseconds);
	// printf("%d microseconds\n", microseconds);
	usleep(microseconds);
}

uint32_t	get_program_time(uint32_t start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);

	return ((current_time.tv_sec - start_time));
}