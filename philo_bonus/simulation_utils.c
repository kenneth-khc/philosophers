/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:45:11 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/29 21:54:56 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#if 0
# include <signal.h>

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

/* Log general simulation messages */
void	log_message(const char *color, t_simulation *sim, const char *msg)
{
	uint32_t	timestamp;

	timestamp = get_time_since(sim->start_time);
	printf("%*u%s %s%s\n", PADDING,
		timestamp, color, msg, COLOR_RESET);
}

/* Log a philo's action */
void	log_philo_action(const char *color, t_philo *philo, const char *msg)
{
	t_simulation	*sim;
	uint32_t		timestamp;

	sim = philo->simulation;
	sem_wait(sim->printer);
	timestamp = get_time_since(sim->start_time);
	printf("%*u%s %d %s%s\n", PADDING,
		timestamp, color, philo->id, msg, COLOR_RESET);
	sem_post(sim->printer);
}

/* Log a philo's death */
void	log_philo_death(const char *color, t_simulation *sim, uint16_t id)
{
	uint32_t	timestamp;

	sem_wait(sim->printer);
	timestamp = get_time_since(sim->start_time);
	printf("%*u%s %d %s%s\n", PADDING,
		timestamp, color, id, "died", COLOR_RESET);
}
