/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:02:02 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/05 19:07:28 by vd-ambro         ###   ########.fr       */
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
	return (return_code);
}