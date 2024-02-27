/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:24:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/27 19:55:57 by kecheong         ###   ########.fr       */
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

	sem_unlink("TEMP");
	sim->temp = sem_open("TEMP", O_CREAT, 0666, 0);
	sem_unlink("FORKS");
	sim->forks = sem_open("FORKS", O_CREAT, 0666, sim->philo_count);
	sem_unlink("MASTER");
	sim->gatekeeper = sem_open("MASTER", O_CREAT, 0666, 1);
	sem_unlink("PRINTER");
	sim->printer = sem_open("PRINTER", O_CREAT, 0666, 1);
	sem_unlink("EAT_COUNTER");
	sim->eat_counter = sem_open("EAT_COUNTER", O_CREAT, 0666, 0);
	sim->philo_semaphores = malloc((sizeof(sem_t *) * (sim->philo_count + 1)));
	if (sim->philo_semaphores == NULL)
		error_and_exit(E_MALLOC_FAILED);
	i = 0;
	char name2[6];
	name2[0] = '2';
	while (i < sim->philo_count)
	{
		generate_semaphore_name(name, i + 1);
		sem_unlink(name);
		generate_semaphore_name(name2 + 1, i + 1);
		sim->philo_semaphores[i] = sem_open(name, O_CREAT, 0666, 1);
		i++;
	}
	sim->philo_semaphores[i] = NULL;
}

#define NIBBLE 4

/** 
 * Generate a unique semaphore name for the philo based on its
 * id and converting it to hexadecimal
 */
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
