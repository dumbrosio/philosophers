/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:48:23 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/05 18:50:59 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	pthread_t *thread_id;
	t_philo *philos;
	t_fork *forks;
	t_params data;
	int num_philos;
	int i;

	num_philos = atoi(argv[1]);
	thread_id = malloc(num_philos * sizeof(pthread_t));
	check_params(&data, argc, argv);
	create_philos(&philos, &forks, &data);
	data.start_time = get_timestamp();

	i = 0;
	while (i < num_philos)
	{
		pthread_create(&thread_id[i], NULL, routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&(forks[i].is_lock));
		i++;
	}
	free(forks);
	free(philos);
	free(thread_id);
	return (0);
}