/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:20:45 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/23 12:03:30 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void
validate_args(char **argv);

static void		
set_simulation_rules(t_simulation *sim, char **args);

static uint64_t	
philo_atoi(char *str);

/**
 * Parse arguments. Only accept positive numbers in the format of 
 * <philo_count> <time_to_die> <time_to_eat> <time_to_sleep> with an
 * optional <times_to_eat>
 */
void	parse_args(int argc, char **argv, t_simulation *args)
{
	if (argc == 5 || argc == 6)
	{
		validate_args(argv + 1);
		set_simulation_rules(args, argv + 1);
	}
	else
		error_and_exit(E_INVALID_ARG_COUNT);
}

/* Invalidate arguments if non number found */
static void	validate_args(char **argv)
{
	uint8_t	i;

	while (*argv != NULL)
	{
		i = 0;
		while ((*argv)[i] != '\0')
		{
			if (!((*argv)[i] >= '0' && (*argv)[i] <= '9'))
				error_and_exit(E_INVALID_ARG_TYPE);
			i++;
		}
		argv++;
	}
}

/* Set rules for philos to follow as according to arguments input */
static void	set_simulation_rules(t_simulation *simulation, char **argv)
{
	t_rules	*rules;

	rules = &simulation->rules;
	simulation->philo_count = philo_atoi(argv[0]);
	rules->time_to_die = philo_atoi(argv[1]);
	rules->time_to_eat = philo_atoi(argv[2]);
	rules->time_to_sleep = philo_atoi(argv[3]);
	if (argv[4])
	{
		rules->eat_limit = true;
		rules->required_meals = philo_atoi(argv[4]);
	}
	else
		rules->eat_limit = false;
}

static uint64_t	philo_atoi(char *str)
{
	uint64_t	num;

	num = 0;
	while (*str != '\0')
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	return (num);
}
