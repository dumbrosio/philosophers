/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:47:39 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/05 18:36:42 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philo *philo, t_fork **forks, t_params *params, int i)
{
	philo->params = params;
	philo->id = i + 1;
	philo->last_meal = 0;
	philo->l_fork = &((*forks)[i]);
	philo->r_fork = &((*forks)[(i + 1) % params->num_philos]);
	pthread_mutex_init(&(philo->l_fork->is_lock), NULL);
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

int	init_params(t_params *params, int argc, char **argv)
{
	if (argc != 5)
	{
		printf("Usage: \
				%s <philo_num> <time_to_die> <time_to_eat> <time_to_sleep>\n",
				argv[0]);
		return (0);
	}
	params->num_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (params->num_philos <= 0)
	{
		printf("Insert a valid number of philosophers.\n");
		return (0);
	}
	return (1);
}
