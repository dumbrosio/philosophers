/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:48:23 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/10/03 18:59:41 by vd-ambro         ###   ########.fr       */
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

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_timestamp();
	while ((get_timestamp() - start_time) < time_in_ms)
		usleep(100);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->l_fork->is_lock));
		printf("%lu %d has taken a fork\n", (get_timestamp()
				- philo->params->start_time), philo->id);
		pthread_mutex_lock(&(philo->r_fork->is_lock));
		printf("%lu %d has taken a fork\n", (get_timestamp()
				- philo->params->start_time), philo->id);
	}
	else
	{
		pthread_mutex_lock(&(philo->r_fork->is_lock));
		printf("%lu %d has taken a fork\n", (get_timestamp()
				- philo->params->start_time), philo->id);
		pthread_mutex_lock(&(philo->l_fork->is_lock));
		printf("%lu %d has taken a fork\n", (get_timestamp()
				- philo->params->start_time), philo->id);
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->l_fork->is_lock));
	pthread_mutex_unlock(&(philo->r_fork->is_lock));
}

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

long	get_meal_interval(t_philo *philo)
{
	return (get_timestamp() - philo->last_meal);
}

void	die(t_philo *philo)
{
	long	meal_interval;

	meal_interval = get_meal_interval(philo);
	if (meal_interval > philo->params->time_to_die)
	{
		printf("%lu Philosopher %d has died\n", (get_timestamp()
				- philo->params->start_time), philo->id);
		exit(1);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = 0;
	while (1)
	{
		take_forks(philo);
		eating(philo);
		release_forks(philo);
		sleeping(philo);
		thinking(philo);
		die(philo);
	}
	return (NULL);
}

int	check_params(int argc, char *argv[], int *num_philos)
{
	if (argc != 5)
	{
		printf("Usage:\
				%s <philo_num> <time_to_die> <time_to_eat> <time_to_sleep>\n",
			argv[0]);
		return (0);
	}
	*num_philos = atoi(argv[1]);
	if (*num_philos <= 0)
	{
		printf("Insert a valid number of philosophers.\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	pthread_t	*thread_id;
	t_philo		*philos;
	t_fork		*forks;
	t_params	data;
	int			num_philos;
	int			i;

	num_philos = atoi(argv[1]);
	thread_id = malloc(num_philos * sizeof(pthread_t));
	philos = malloc(num_philos * sizeof(t_philo));
	forks = malloc(num_philos * sizeof(t_fork));
	if (thread_id == NULL || philos == NULL || forks == NULL)
		return (1);
	if (!check_params(argc, argv, &num_philos))
		return (1);
	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&(forks[i].is_lock), NULL);
		i++;
	}
	data.num_philos = atoi(argv[1]);
	data.time_to_die = atoi(argv[2]);
	data.time_to_eat = atoi(argv[3]);
	data.time_to_sleep = atoi(argv[4]);
	data.start_time = get_timestamp();
	i = 0;
	while (i < num_philos)
	{
		philos[i].params = &data;
		philos[i].id = i + 1;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % num_philos];
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
