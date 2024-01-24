/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:18:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/01/24 20:58:09 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *printer(void *arg)
{
	(void)arg;
	static int i = 0;
	pthread_mutex_t mutex;
	pthread_mutex_lock(&mutex);
	printf("Execute from thread %d\n", ++i);
	
	return (NULL);
}

void	*philosophize(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)(arg);

	// printf(">> Philo ID %d <<\n", philo->id);
	// printf(">> State    %d <<\n", philo->state);
	// printf(">> %p %p\n\n", philo->left_hand, philo->right_hand);
	while (philo_is_alive(philo))
	{
		if (philo->state == THINKING)
		{
			pick_up_left_fork(philo);
			pick_up_right_fork(philo);
			munch_munch(philo);
		}
		if (philo->state == EATING)
		{
			philo_sleeping(philo);
		}
	}
	printf(RED"%.10u %d died\n"COLOR_RESET,
		get_program_time(philo->start_time), philo->id);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_simulation	args;
	
	parse_args(argc, argv, &args);
	printf(GRN"%.10u Simulation started\n"COLOR_RESET, get_program_time(args.start_time));
	args.philos = malloc(sizeof(*args.philos) * args.philo_count);
	args.forks = malloc(sizeof(*args.forks) * args.philo_count);
	init_mutexes(args.forks, args.philo_count);
	// int i = 0;
	// while (i < args.philo_count)
	// {
	// 	printf(">>> %p\n", &args.forks[i]);
	// 	i++;
	// }
	printf("\n");
	init_philos(&args.philos, &args);
}

void	init_mutexes(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}	
}

void	init_philos(t_philosopher **philos, t_simulation *args)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].state = THINKING;
		(*philos)[i].rules = args->rules;
		(*philos)[i].start_time = args->start_time;
		(*philos)[i].last_meal_time = args->start_time;
		init_hands(&(*philos)[i], args);
		pthread_create(&(*philos)[i].thread, NULL, philosophize, &(*philos)[i]);
		i++;
	}
	i = 0;
	while (i < args->philo_count)
	{
		pthread_join((*philos)[i].thread, NULL);
		i++;
	}	
}

void	init_hands(t_philosopher *philo, t_simulation *sim)
{
	if (philo->id == 1)
	{
		philo->left_hand = &sim->forks[sim->philo_count - 1];
		philo->right_hand = &sim->forks[0];
	}
	else
	{
		philo->left_hand = &sim->forks[philo->id - 2];
		philo->right_hand = &sim->forks[philo->id - 1];
	}
	// printf("ID %d\n", philo->id);
	// printf("%p %p\n", philo->left_hand, philo->right_hand);
}
