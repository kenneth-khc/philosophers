/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 05:28:08 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/01 08:44:46 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	color_printf(const char *color, uint64_t timestamp, uint16_t id,
const char *message)
{
	if (id)
		printf("%llu %s%d %s%s\n",
			timestamp, color, id, message, COLOR_RESET);
	else if (id == 0)
		printf("%s%llu %s%s\n",
			color, timestamp, message, COLOR_RESET);
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
		if (philo->eat_count < (uint64_t)philos->rules->min_eat)
			return (pthread_mutex_unlock(&philo->eat_count_mutex), true);
		pthread_mutex_unlock(&philo->eat_count_mutex);
		i++;
	}
	return (kill_all_philos(philo_count, philos), false);
}

bool	philo_is_alive(t_philosopher *philo)
{
	bool	alive;

	pthread_mutex_lock(&philo->alive_mutex);
	alive = philo->alive;
	return (pthread_mutex_unlock(&philo->alive_mutex), alive);
}
