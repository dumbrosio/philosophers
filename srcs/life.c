/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:46:52 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/17 15:33:51 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->last_meal_time_m));
	philo->last_meal_time = get_timestamp() - philo->params->start_time;
	pthread_mutex_unlock(&(philo->last_meal_time_m));
	write_state("is eating", philo);
	ft_usleep(philo->params->time_to_eat);
}

void	sleeping(t_philo *philo)
{
	write_state("is sleeping", philo);
	ft_usleep(philo->params->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	write_state("is thinking", philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(philo->params->time_to_eat);
	while (!is_dead(philo))
	{
		if (philo->params->num_philos > 1)
		{
			take_forks(philo);
			eating(philo);
			release_forks(philo);
			sleeping(philo);
			thinking(philo);
		}
	}
	return (NULL);
}
