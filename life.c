/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:46:52 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/08 20:40:47 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo)
{
	write_state("is eating", philo);
	ft_usleep(philo->params->time_to_eat);
	philo->meal_count++;
	philo->last_meal_time = get_timestamp() - philo->params->start_time;
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
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(philo->params->time_to_eat);
	while (!is_dead(philo))
	{
		if (philo->meal_count >= philo->params->num_of_meals
			&& philo->params->num_of_meals > 0)
			break ;
		take_forks(philo);
		eating(philo);
		release_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}