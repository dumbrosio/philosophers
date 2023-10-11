/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:46:52 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/11 17:12:45 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(philo->params->time_to_eat);
	while (!is_dead(philo))
	{
		if (philo->meal_count >= philo->params->num_of_meals &&
			philo->params->num_of_meals > 0)
			break ;
		take_fork('l', philo);
		if (philo->l_taken)
			take_fork('r', philo);
		if (philo->r_taken && philo->l_taken)
		{
			write_state("is eating", philo);
			ft_usleep(philo->params->time_to_eat);
			philo->meal_count++;
			pthread_mutex_lock(&(philo->last_meal_m));
			philo->last_meal_time = get_timestamp() - philo->params->start_time;
			pthread_mutex_unlock(&(philo->last_meal_m));
			release_forks_and_sleep(philo);
			write_state("is thinking", philo);
		}
	}
	return (NULL);
}