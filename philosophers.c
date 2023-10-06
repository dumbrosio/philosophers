/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:48:23 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/06 11:49:23 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_params	data;
	t_philo		*philos;
	t_fork		*forks;

	check_params(&data, argc, argv);
	create_philos(&philos, &forks, &data);
	pthread_mutex_init(&(data.console_m), NULL);
	create_threads(&philos, &data);
	wait_threads(&philos, &data);
	free(philos);
	free(forks);
}