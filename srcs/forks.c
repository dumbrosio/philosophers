/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:45:41 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/09 13:52:43 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->l_fork->fork_m));
		write_state("has taken a fork", philo);
		pthread_mutex_lock(&(philo->r_fork->fork_m));
		write_state("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(&(philo->r_fork->fork_m));
		write_state("has taken a fork", philo);
		pthread_mutex_lock(&(philo->l_fork->fork_m));
		write_state("has taken a fork", philo);
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->l_fork->fork_m));
	pthread_mutex_unlock(&(philo->r_fork->fork_m));
}