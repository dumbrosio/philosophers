/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:48:23 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/11 17:04:40 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	free_all(t_philo *philos, t_fork *forks, int exit_code)
{
	free(philos);
	free(forks);
	return (exit_code);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philos;
	t_fork		*forks;
	int			return_code;

	return_code = EXIT_SUCCESS;
	if (!init_params(&params, argc, argv))
		return (EXIT_FAILURE);
	if (!create_philos(&philos, &forks, &params))
		return (EXIT_FAILURE);
	if (!create_threads(&philos, &params))
		return_code = stop_threads(&philos[0]);
	if (!wait_threads(&philos, &params))
		return (free_all(philos, forks, EXIT_FAILURE));
	return (free_all(philos, forks, return_code));
}