/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:41:55 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/31 23:48:54 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	philo_itoa(int num, char *original);
static uint8_t	get_num_len(int num);
static bool		invalid_arg(char *original, char *reconverted);

t_status	validate_rules(t_simulation *simulation, char **args)
{
	t_status	status;
	t_rules		*rules;

	rules = &simulation->rules;
	status = philo_itoa(simulation->philo_count, args[1]);
	if (status == SUCCESS)
		status = philo_itoa(rules->time_to_die, args[2]);
	if (status == SUCCESS)
		status = philo_itoa(rules->time_to_eat, args[3]);
	if (status == SUCCESS)
		status = philo_itoa(rules->time_to_sleep, args[4]);
	if (status == SUCCESS)
		if (rules->min_eat != -1)
			status = philo_itoa(rules->min_eat, args[5]);
	return (status);
}

static t_status	philo_itoa(int num, char *original)
{
	uint8_t	digits;
	char	*res;

	digits = get_num_len(num);
	res = malloc(sizeof(*res) * (digits + 1));
	if (!res)
		return (E_MALLOC_FAILED);
	res[digits] = '\0';
	while (digits > 0)
	{
		digits--;
		res[digits] = num % 10 + '0';
		num /= 10;
	}
	if (invalid_arg(res, original))
	{
		free(res);
		return (E_INVALID_ARG_TYPE);
	}
	free(res);
	return (SUCCESS);
}

static uint8_t	get_num_len(int num)
{
	uint8_t	len;

	len = 0;
	if (num == 0)
		return (len = 1);
	while (num > 0)
	{
		num /= 10;
		len += 1;
	}
	return (len);
}

static bool	invalid_arg(char *original, char *reconverted)
{
	while (*reconverted)
	{
		if (*reconverted != *original)
			return (true);
		reconverted++;
		original++;
	}
	return (false);
}

#define MALLOC_FAILED_ERR "Malloc failed\n"
#define INVALID_ARG_COUNT_ERR "Invalid number of arguments.\n"
#define USAGE "Usage: <number_of_philosophers> <time_to_die> <time_to_eat>"
#define USAGE2 "<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
#define ARG_TYPE_ERR "Invalid argument type.\nArguments should be numbers.\n"
#define THREAD_FAILED_ERR "Thread failed\n"

void	handle_errors(t_status status)
{
	if (status == E_MALLOC_FAILED)
		write(STDERR_FILENO, MALLOC_FAILED_ERR, sizeof(MALLOC_FAILED_ERR) - 1);
	else if (status == E_INVALID_ARG_COUNT)
	{
		write(STDERR_FILENO,
			INVALID_ARG_COUNT_ERR, sizeof(INVALID_ARG_COUNT_ERR) - 1);
		write(STDERR_FILENO, USAGE, sizeof(USAGE) - 1);
		write(STDERR_FILENO, USAGE2, sizeof(USAGE2) - 1);
	}
	else if (status == E_INVALID_ARG_TYPE)
		write(STDERR_FILENO,
			ARG_TYPE_ERR, sizeof(ARG_TYPE_ERR) - 1);
	else if (status == E_THREAD_FAILED)
		write(STDERR_FILENO, THREAD_FAILED_ERR, sizeof(THREAD_FAILED_ERR) - 1);
}
