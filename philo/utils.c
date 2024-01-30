/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 05:28:08 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/29 23:19:55 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	color_printf(const char *color, uint64_t start_time, uint16_t id,
const char *message)
{
	if (id)
		printf("%.10llu %s%d %s%s\n",
			get_time_since(start_time), color, id, message, COLOR_RESET);
	else if (id == 0)
		printf("%s%.10llu %s%s\n",
			color, get_time_since(start_time), message, COLOR_RESET);
}

bool	check_eat_count(uint16_t philo_count, t_philosopher *philos)
{
	int				i;
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

bool	philo_is_alive(t_philosopher *philo)
{
	bool	alive;

	pthread_mutex_lock(&philo->alive_mutex);
	alive = philo->alive;
	pthread_mutex_unlock(&philo->alive_mutex);
	return (alive);
}
