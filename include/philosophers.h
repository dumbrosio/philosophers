/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:42:59 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/11 14:33:26 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_params
{
	int				is_dead;
	int				num_of_meals;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	pthread_mutex_t	console_m;
	pthread_mutex_t	is_dead_m;
	pthread_t		death;
}					t_params;

typedef struct s_fork
{
	pthread_mutex_t	fork_m;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	long			last_meal_time;
	pthread_mutex_t	last_meal_m;
	pthread_t		life;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_params		*params;
}					t_philo;

// init
int					create_philos(t_philo **philos, t_fork **forks,
						t_params *params);
int					init_params(t_params *params, int argc, char **argv);

// forks
void				take_forks(t_philo *philo);
void				release_forks(t_philo *philo);

// life
void				*routine(void *arg);

// death
void				*check_philos_death(void *arg);
int					is_dead(t_philo *philo);

// threads.c
int					create_threads(t_philo **philos, t_params *params);
int					wait_threads(t_philo **philos, t_params *params);
int					stop_threads(t_philo *philo);

//utils
long				get_timestamp(void);
void				ft_usleep(long int ms);
int					ft_atoi(const char *str);
void				write_state(char *str, t_philo *philo);