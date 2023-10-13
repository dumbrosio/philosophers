/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:48:04 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/13 17:42:54 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_philo_death(t_philo *philo, long timestamp)
{
	int		dead;
	long	last_meal_time;

	dead = 0;
	pthread_mutex_lock(&(philo->last_meal_m));
	last_meal_time = timestamp - philo->last_meal_time;
	pthread_mutex_unlock(&(philo->last_meal_m));
	if (last_meal_time > philo->params->time_to_die)
	{
		pthread_mutex_lock(&(philo->params->is_dead_m));
		philo->params->is_dead = 1;
		pthread_mutex_unlock(&(philo->params->is_dead_m));
		dead = 1;
		pthread_mutex_lock(&(philo->params->console_m));
		printf("%03ld %d died\n", timestamp, philo->id + 1);
		pthread_mutex_unlock(&(philo->params->console_m));
	}
	return (dead);
}

void	*check_philos_death(void *arg)
{
	t_params	*params;
	t_philo		**philos;
	long		timestamp;
	int			i;

	philos = (t_philo **)arg;
	params = philos[0]->params;
	while (1)
	{
		i = 0;
		timestamp = get_timestamp() - params->start_time;
		while (i < params->num_philos)
		{
			if (check_philo_death(&(*philos)[i], timestamp))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

int	is_dead(t_philo *philo)
{
	int dead;

	pthread_mutex_lock(&(philo->params->is_dead_m));
	dead = philo->params->is_dead;
	pthread_mutex_unlock(&(philo->params->is_dead_m));
	return (dead);
}