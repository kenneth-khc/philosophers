/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 05:28:08 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/27 09:43:19 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	color_printf(const char *color, uint64_t start_time, uint16_t id,
const char *message)
{
	printf("%s", color);
	printf("%.10llu ", get_time_since(start_time));
	if (id > 0)
		printf("%d ", id);
	printf("%s", message);
	// printf(COLOR_RESET);
	// fflush(stdout);
}

bool	check_eat_count(uint16_t philo_count, t_philosopher *philos)
{
	int	i;
	t_philosopher	*philo;

	i = 0;
	while (i < philo_count)
	{
		philo = &philos[i];
		pthread_mutex_lock(&philo->eat_count_mutex);
		if (philo->eat_count < (uint64_t)philos->rules.min_eat)
		{
			pthread_mutex_unlock(&philo->eat_count_mutex);
			return (true);
		}
		pthread_mutex_unlock(&philo->eat_count_mutex);
		i++;
	}
	kill_all_philos(philo_count, philos);
	return (false);
}
