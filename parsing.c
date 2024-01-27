/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:20:45 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/27 09:33:21 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_atoi(char *str);

void	print_simulation_struct(t_simulation *args)
{
	printf("philo_count:   %d\n", args->philo_count);
	printf("time_to_die:   %llu\n", args->rules.time_to_die);
	printf("time_to_eat:   %llu\n", args->rules.time_to_eat);
	printf("time_to_sleep: %llu\n", args->rules.time_to_sleep);
	printf("min_eat:	 %lld\n", args->rules.min_eat);
	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
}

void	parse_args(int argc, char **argv, t_simulation *args)
{
	struct timeval	current_time;

	if (argc == 5 || argc == 6)
	{	
		args->philo_count = philo_atoi(argv[1]);
		args->rules.time_to_die = philo_atoi(argv[2]);
		args->rules.time_to_eat = philo_atoi(argv[3]);
		args->rules.time_to_sleep = philo_atoi(argv[4]);
		if (argv[5])
			args->rules.min_eat = philo_atoi(argv[5]);
		else
			args->rules.min_eat = -1;
		gettimeofday(&current_time, NULL);
		args->start_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
		printf(">>> START %llu\n", args->start_time);
	}
	else
	{
		printf("Invalid number of arguments.\n");
		printf("Usage: <number_of_philosophers> "
		"<time_to_die> <time_to_eat> <time_to_sleep> " 
		"[number_of_times_each_philosopher_must_eat]\n");
		exit(EXIT_FAILURE);
	}
	print_simulation_struct(args);
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
