/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:42:59 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/05 16:54:24 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_params
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
}					t_params;

typedef struct s_fork
{
	pthread_mutex_t	is_lock;
}					t_fork;

typedef struct s_philo
{
	t_params		*params;
	int				id;
	long			last_meal;
	t_fork			*l_fork;
	t_fork			*r_fork;
}					t_philo;

// init
void				init_philo(t_philo *philo, t_fork **forks, t_params *params,
						int i);
int					create_philos(t_philo **philos, t_fork **forks,
						t_params *params);
int					init_params(t_params *params, int argc, char **argv);

// forks
void				take_forks(t_philo *philo);
void				release_forks(t_philo *philo);

// life
void				eating(t_philo *philo);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				*routine(void *arg);

// death
long				get_meal_interval(t_philo *philo);
void				die(t_philo *philo);

//utils
long				get_timestamp(void);
void				ft_usleep(long int time_in_ms);
