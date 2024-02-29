/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:24:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/29 21:49:37 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void
generate_semaphore_name(char *name, uint16_t philo_id);

/* Initialize semaphores for synchronization */
void	init_semaphores(t_simulation *sim)
{
	char		name[5];
	uint16_t	i;

	sem_unlink("FORKS");
	sem_unlink("PRINTER");
	sem_unlink("EAT_COUNTER");
	sim->forks = sem_open("FORKS", O_CREAT, 0666, sim->philo_count);
	sim->printer = sem_open("PRINTER", O_CREAT, 0666, 1);
	sim->eat_counter = sem_open("EAT_COUNTER", O_CREAT, 0666, 0);
	sim->mealtime_semaphores
		= malloc((sizeof(sem_t *) * (sim->philo_count + 1)));
	if (sim->mealtime_semaphores == NULL)
		error_and_exit(E_MALLOC_FAILED);
	i = 0;
	while (i < sim->philo_count)
	{
		generate_semaphore_name(name, i + 1);
		sem_unlink(name);
		sim->mealtime_semaphores[i] = sem_open(name, O_CREAT, 0666, 1);
		i++;
	}
	sim->mealtime_semaphores[i] = NULL;
}

/** 
 * Generate a unique semaphore name for the philo based on its
 * id and converting it to hexadecimal
 */

#define NIBBLE 4

static void	generate_semaphore_name(char *name, uint16_t philo_id)
{
	const char	base16[] = "0123456789ABCDEF";
	uint8_t		hex_digits;

	hex_digits = 4;
	name[hex_digits] = '\0';
	while (hex_digits > 0)
	{
		hex_digits--;
		name[hex_digits] = base16[philo_id & 0xF];
		philo_id >>= NIBBLE;
	}
}
