/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:20:45 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/21 21:32:10 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_status
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
t_status	parse_args(int argc, char **argv, t_simulation *args)
{
	t_status	status;

	if (argc == 5 || argc == 6)
	{
		status = validate_args(argv + 1);
		if (status == SUCCESS)
			set_simulation_rules(args, argv + 1);
	}
	else
		status = E_INVALID_ARG_COUNT;
	return (status);
}

/* Invalidate arguments if non number found */
static t_status	validate_args(char **argv)
{
	uint8_t	i;

	while (*argv != NULL)
	{
		i = 0;
		while ((*argv)[i] != '\0')
		{
			if (!((*argv)[i] >= '0' && (*argv)[i] <= '9'))
				return (E_INVALID_ARG_TYPE);
			i++;
		}
		argv++;
	}
	return (SUCCESS);
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
