/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:45:41 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/11 17:14:16 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_fork(char fork_side, t_philo *philo)
{
	int		*taken;
	t_fork	*fork;

	if (!is_dead(philo))
	{
		taken = &(philo->r_taken);
		fork = philo->r_fork;
		if (fork_side == 'l')
		{
			taken = &(philo->l_taken);
			fork = philo->l_fork;
		}
		pthread_mutex_lock(&(fork->fork_m));
		if (!(*taken) && !fork->used)
		{
			*taken = 1;
			fork->used = 1;
			pthread_mutex_unlock(&(fork->fork_m));
			write_state("has taken a fork", philo);
		}
		else
			pthread_mutex_unlock(&(fork->fork_m));
	}
}

void	release_fork(char fork_side, t_philo *philo)
{
	int		*taken;
	t_fork	*fork;

	taken = &(philo->r_taken);
	fork = philo->r_fork;
	if (fork_side == 'l')
	{
		taken = &(philo->l_taken);
		fork = philo->l_fork;
	}
	pthread_mutex_lock(&(fork->fork_m));
	*taken = 0;
	fork->used = 0;
	pthread_mutex_unlock(&(fork->fork_m));
}

void	release_forks_and_sleep(t_philo *philo)
{
	release_fork('r', philo);
	release_fork('l', philo);
	write_state("is sleeping", philo);
	ft_usleep(philo->params->time_to_sleep);
}