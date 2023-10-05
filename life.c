/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:46:52 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/05 16:54:32 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo)
{
	printf("%lu %d is eating\n", (get_timestamp() - philo->params->start_time),
			philo->id);
	philo->last_meal = get_timestamp();
	ft_usleep(philo->params->time_to_eat);
}

void	thinking(t_philo *philo)
{
	printf("%lu %d is thinking\n", (get_timestamp()
				- philo->params->start_time), philo->id);
}

void	sleeping(t_philo *philo)
{
	printf("%lu %d is sleeping\n", (get_timestamp()
				- philo->params->start_time), philo->id);
	ft_usleep(philo->params->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->last_meal = 0;
	while (1)
	{
		take_forks(philo);
		eating(philo);
		release_forks(philo);
		sleeping(philo);
		die(philo);
		thinking(philo);
	}
	return (NULL);
}