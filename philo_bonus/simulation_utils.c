/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:45:11 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/28 17:39:03 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Return a philo's alive state */
bool	philo_is_alive(t_philo *philo)
{
	return (philo->alive);
}

#if 1
#include <signal.h>
void	flush_output(int signum)
{
	(void)signum;
	fflush(stdout);
	exit(EXIT_SUCCESS);
}

void	set_sigterm_handler(void)
{
	signal(SIGTERM, flush_output);
}
#endif