/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:41:55 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/29 17:11:51 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static enum e_status philo_itoa(int num, char *original);
static uint8_t get_num_len(int num);
static bool	invalid_arg(char *original, char *reconverted);

enum e_status	validate_rules(t_rules *rules, char **args)
{
	enum e_status	status;

	status = philo_itoa(rules->philo_count, args[1]);
	if (status != SUCCESS)
		return (status);
	status = philo_itoa(rules->time_to_die, args[2]);
	if (status != SUCCESS)
		return (status);
	status = philo_itoa(rules->time_to_eat, args[3]);
	if (status != SUCCESS)
		return (status);
	status = philo_itoa(rules->time_to_sleep, args[4]);
	if (status != SUCCESS)
		return (status);
	if (rules->min_eat != -1)
		status = philo_itoa(rules->min_eat, args[5]);
	return (status);
}

static enum e_status philo_itoa(int num, char *original)
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

static uint8_t get_num_len(int num)
{
	uint8_t len;

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

void	handle_error(enum e_status status)
{
	if (status == E_MALLOC_FAILED)
		printf("Malloc failed\n");
	if (status == E_INVALID_ARG_COUNT)
	{
		printf("Invalid number of arguments.\n");
		printf("Usage: <number_of_philosophers> "
			"<time_to_die> <time_to_eat> <time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]\n");
	}
	else if (status == E_INVALID_ARG_TYPE)
	{
		printf("wrong format bozo\n");
	}
}
