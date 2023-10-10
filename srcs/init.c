/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:47:39 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/10 11:44:11 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philo *philo, t_fork **forks, t_params *params, int i)
{
	philo->id = i;
	philo->last_meal_time = 0;
	philo->meal_count = 0;
	philo->params = params;
	philo->l_fork = &((*forks)[i]);
	philo->r_fork = &((*forks)[(i + 1) % params->num_philos]);
	pthread_mutex_init(&(philo->l_fork->fork_m), NULL);
	pthread_mutex_init(&(philo->r_fork->fork_m), NULL);
}

int	create_philos(t_philo **philos, t_fork **forks, t_params *params)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * params->num_philos);
	if (!(*philos))
		return (0);
	*forks = malloc(sizeof(t_fork) * params->num_philos);
	if (!(*forks))
	{
		free(*philos);
		return (0);
	}
	i = 0;
	while (i < params->num_philos)
	{
		init_philo(&(*philos)[i], forks, params, i);
		i++;
	}
	return (1);
}

int	check_params(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s <num_philos> <time_to_die> ", argv[0]);
		printf("<time_to_eat> <time_to_sleep> [num_of_meals]\n ");
		return (0);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 0 ||
		ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
	{
		printf("Invalid value.\n");
		return (0);
	}
	if (argc > 5 && ft_atoi(argv[5]) < 0)
	{
		printf("Invalid option.\n");
		return (0);
	}
	return (1);
}

int	init_params(t_params *params, int argc, char **argv)
{
	if (!check_params(argc, argv))
		return (0);
	else
	{
		params->is_dead = 0;
		params->num_of_meals = -1;
		params->num_philos = ft_atoi(argv[1]);
		params->time_to_die = ft_atoi(argv[2]);
		params->time_to_eat = ft_atoi(argv[3]);
		params->time_to_sleep = ft_atoi(argv[4]);
		if (argc > 5)
			params->num_of_meals = ft_atoi(argv[5]);
		if (params->num_philos == 1)
		{
			pthread_mutex_lock(&(params->console_m));
			printf("000 1 is thinking \"Oh no!\".\n");
			printf("001 1 has taken a fork.\n");
			printf("%d 1 died.\n", params->time_to_die + 1);
			pthread_mutex_unlock(&(params->console_m));
			exit(EXIT_SUCCESS);
		}
		pthread_mutex_init(&(params->console_m), NULL);
		pthread_mutex_init(&(params->is_dead_m), NULL);
	}
	return (1);
}