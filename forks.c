/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:45:41 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/08 15:27:29 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	t_fork	*left_side;
	t_fork	*right_side;

	if (philo->id % 2 == 0)
	{
		left_side = philo->l_fork;
		right_side = philo->r_fork;
	}
	else
	{
		left_side = philo->r_fork;
		right_side = philo->l_fork;
	}
	pthread_mutex_lock(&(left_side->fork_m));
	write_state("has taken a fork", philo);
	pthread_mutex_lock(&(right_side->fork_m));
	write_state("has taken a fork", philo);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->l_fork->fork_m));
	pthread_mutex_unlock(&(philo->r_fork->fork_m));
}