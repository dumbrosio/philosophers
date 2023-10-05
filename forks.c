/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:45:41 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/05 16:54:35 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->l_fork->is_lock));
		printf("%lu %d has taken a fork\n", (get_timestamp()
					- philo->params->start_time), philo->id);
		pthread_mutex_lock(&(philo->r_fork->is_lock));
		printf("%lu %d has taken a fork\n", (get_timestamp()
					- philo->params->start_time), philo->id);
	}
	else
	{
		pthread_mutex_lock(&(philo->r_fork->is_lock));
		printf("%lu %d has taken a fork\n", (get_timestamp()
					- philo->params->start_time), philo->id);
		pthread_mutex_lock(&(philo->l_fork->is_lock));
		printf("%lu %d has taken a fork\n", (get_timestamp()
					- philo->params->start_time), philo->id);
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->l_fork->is_lock));
	pthread_mutex_unlock(&(philo->r_fork->is_lock));
}