/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:20:45 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/03 22:17:10 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status
validate_args(char **argv);

static void		
set_simulation_rules(t_simulation *sim, char **args);

static uint64_t	
philo_atoi(char *str);

t_status	parse_args(int argc, char **argv, t_simulation *args)
{
	t_status	status;

	if (argc == 5 || argc == 6)
	{
		status = validate_args(argv + 1);
		if (status == SUCCESS)
			set_simulation_rules(args, argv);
	}
	else
		status = E_INVALID_ARG_COUNT;
	return (status);
}

static t_status	validate_args(char **argv)
{
	uint8_t	i;

	while (*argv != NULL)
	{
		i = 0;
		while ((*argv)[i] != '\0')
		{
			if (**argv < '0' && **argv > '9')
				return (E_INVALID_ARG_TYPE);
			i++;
		}
		argv++;
	}
	return (SUCCESS);
}

static void	set_simulation_rules(t_simulation *sim, char **argv)
{
	t_rules	*rules;

	rules = &sim->rules;
	sim->philo_count = philo_atoi(argv[1]);
	rules->time_to_die = philo_atoi(argv[2]);
	rules->time_to_eat = philo_atoi(argv[3]);
	rules->time_to_sleep = philo_atoi(argv[4]);
	if (argv[5])
		rules->min_eat = philo_atoi(argv[5]);
	else
		rules->min_eat = -1;
}

static uint64_t	philo_atoi(char *str)
{
	uint64_t	num;

	num = 0;
	while (*str)
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	return (num);
}

#define ARG_COUNT_ERR "Invalid number of args\n"
#define USAGE "Usage: <number_of_philosophers> <time_to_die> <time_to_eat>"
#define USAGE2 "<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
#define ARG_TYPE_ERR "Invalid args.\nArgs should be positive numbers\n"
#define MALLOC_ERR "Malloc failed\n"
#define THREAD_ERR "Thread failed\n"

void	handle_errors(t_status status)
{
	if (status == E_INVALID_ARG_COUNT)
	{
		write(STDERR_FILENO,
			ARG_COUNT_ERR, sizeof(ARG_COUNT_ERR) - 1
			);
		write(STDERR_FILENO,
			USAGE, sizeof(USAGE) - 1
			);
		write(STDERR_FILENO,
			USAGE2, sizeof(USAGE2) - 1
			);
	}
	else if (status == E_INVALID_ARG_TYPE)
		write(STDERR_FILENO,
			ARG_TYPE_ERR, sizeof(ARG_TYPE_ERR) - 1
			);
	else if (status == E_MALLOC_FAILED)
		write(STDERR_FILENO,
			MALLOC_ERR, sizeof(MALLOC_ERR) - 1
			);
	else if (status == E_THREAD_FAILED)
		write(STDERR_FILENO,
			THREAD_ERR, sizeof(THREAD_ERR) - 1
			);
}
