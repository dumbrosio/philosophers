/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:02:02 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/16 17:26:31 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_philo **philos, t_params *params)
{
	int	i;

	params->start_time = get_timestamp();
	i = 0;
	while (i < params->num_philos)
	{
		if (pthread_create(&((*philos)[i].life), NULL, routine,
			&((*philos)[i])))
			return (0);
		i++;
	}
	if (pthread_create(&(params->death), NULL, check_philos_death, philos))
		return (0);
	return (1);
}

int	wait_threads(t_philo **philos, t_params *params)
{
	int	i;
	int	return_code;

	i = 0;
	return_code = 1;
	while (i < params->num_philos)
	{
		if (pthread_join((*philos)[i].life, NULL))
			return_code = 0;
		i++;
	}
	if (pthread_detach((*philos)->params->death))
		return_code = 0;
	return (return_code);
}

int	stop_threads(t_philo *philo)
{
	pthread_mutex_lock(&(philo->params->is_dead_m));
	philo->params->is_dead = 1;
	pthread_mutex_unlock(&(philo->params->is_dead_m));
	return (EXIT_FAILURE);
}
