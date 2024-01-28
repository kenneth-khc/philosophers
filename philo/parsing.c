/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:20:45 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/28 16:51:23 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_atoi(char *str);
static void	set_simulation_rules(t_simulation *sim, char **args);

void	print_simulation_struct(t_simulation *args)
{
	printf("philo_count:   %d\n", args->philo_count);
	printf("time_to_die:   %llu\n", args->rules.time_to_die);
	printf("time_to_eat:   %llu\n", args->rules.time_to_eat);
	printf("time_to_sleep: %llu\n", args->rules.time_to_sleep);
	printf("min_eat:	 %lld\n", args->rules.min_eat);
	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
}

bool	parse_args(int argc, char **argv, t_simulation *args)
{
	if (argc == 5 || argc == 6)
	{
		set_simulation_rules(args, argv);
		return (true);
	}
	else
	{
		printf("Invalid number of arguments.\n");
		printf("Usage: <number_of_philosophers> "
			"<time_to_die> <time_to_eat> <time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]\n");
		return (false);
	}
	print_simulation_struct(args);
}

static void	set_simulation_rules(t_simulation *sim, char **args)
{
	struct timeval	time_now;

	sim->philo_count = philo_atoi(args[1]);
	sim->rules.time_to_die = philo_atoi(args[2]);
	sim->rules.time_to_eat = philo_atoi(args[3]);
	sim->rules.time_to_sleep = philo_atoi(args[4]);
	if (args[5])
		sim->rules.min_eat = philo_atoi(args[5]);
	else
		sim->rules.min_eat = -1;
	gettimeofday(&time_now, NULL);
	sim->start_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	printf(">>> START %llu\n", sim->start_time);
}

static int	philo_atoi(char *str)
{
	int	num;

	num = 0;
	while (*str)
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	return (num);
}