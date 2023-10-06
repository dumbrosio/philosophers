/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:48:04 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/06 11:49:07 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_meal_interval(t_philo *philo)
{
	return (get_timestamp() - philo->last_meal);
}

void	die(t_philo *philo)
{
	long	meal_interval;

	meal_interval = get_meal_interval(philo);
	if (meal_interval > philo->params->time_to_die)
	{
		pthread_mutex_lock(&(philo->params->console_m));
		printf("%lu Philosopher %d has died\n", (get_timestamp()
					- philo->params->start_time), philo->id);
		pthread_mutex_unlock(&(philo->params->console_m));
		exit(1);
	}
}
