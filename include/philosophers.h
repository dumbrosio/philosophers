/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:42:59 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/11 17:18:19 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

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
	int				used;
	pthread_mutex_t	fork_m;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				l_taken;
	int				meal_count;
	int				r_taken;
	long			last_meal_time;
	pthread_mutex_t	last_meal_m;
	pthread_t		life;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_params		*params;
}					t_philo;

// init
int					create_philos(t_philo **philos, t_fork **forks, t_params *params);
int					init_params(t_params *params, int argc, char **argv);

// forks
void				release_forks_and_sleep(t_philo *philo);
void				take_fork(char fork_id, t_philo *philo);

// threads.c
int					create_threads(t_philo **philos, t_params *params);
int					stop_threads(t_philo *philo);
int					wait_threads(t_philo **philos, t_params *params);

// life
void				*routine(void *arg);

// death
void				*check_philos_death(void *arg);
int					is_dead(t_philo *philo);

//utils
int					ft_atoi(const char *str);
long				get_timestamp(void);
void				ft_usleep(long int ms);
void				write_state(char *str, t_philo *philo);
#endif