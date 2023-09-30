#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_params
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
}					t_params;

typedef struct
{
	pthread_mutex_t	is_lock;
}					Fork;

typedef struct
{
	t_params		*params;
	int				id;
	Fork			*l_fork;
	Fork			*r_fork;
}					Philo;

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

void	take_forks(Philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->l_fork->is_lock));
		printf("%lu Philosopher %d has taken fork L\n", (get_timestamp()
					- philo->params->start_time), philo->id);
		pthread_mutex_lock(&(philo->r_fork->is_lock));
		printf("%lu Philosopher %d has taken fork R\n", (get_timestamp()
					- philo->params->start_time), philo->id);
	}
	else
	{
		pthread_mutex_lock(&(philo->r_fork->is_lock));
		printf("%lu Philosopher %d has taken fork R\n", (get_timestamp()
					- philo->params->start_time), philo->id);
		pthread_mutex_lock(&(philo->l_fork->is_lock));
		printf("%lu Philosopher %d has taken fork L\n", (get_timestamp()
					- philo->params->start_time), philo->id);
	}
}

void	release_forks(Philo *philo)
{
	pthread_mutex_unlock(&(philo->l_fork->is_lock));
	pthread_mutex_unlock(&(philo->r_fork->is_lock));
	printf("%lu Philosopher %d released forks\n", (get_timestamp()
				- philo->params->start_time), philo->id);
}

void	*routine(void *arg)
{
	Philo	*philo;

	philo = (Philo *)arg;
	while (1)
	{
		printf("%lu Philosopher %d is thinking\n", (get_timestamp()
					- philo->params->start_time), philo->id);
		sleep(1);
		take_forks(philo);
		printf("%lu Philosopher %d is eating\n", (get_timestamp()
					- philo->params->start_time), philo->id);
		sleep(1);
		release_forks(philo);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int			num_philos;
	pthread_t	thread_id[num_philos];
	Philo		philos[num_philos];
	Fork		forks[num_philos];
	t_params	data;

	if (argc != 2)
	{
		printf("Usage: %s <philo_num>\n", argv[0]);
		return (1);
	}
	num_philos = atoi(argv[1]);
	if (num_philos <= 0)
	{
		printf("Insert a valid number of philosophers.\n");
		return (1);
	}
	// Init philos
	for (int i = 0; i < num_philos; i++)
	{
		pthread_mutex_init(&(forks[i].is_lock), NULL);
		philos[i].params = &data;
	}
	//data.time_to_die = atoi(argv[2]);
	//data.time_to_eat = atoi(argv[3]);
	//data.time_to_sleep = atoi(argv[4]);
	data.start_time = get_timestamp();
	//printf("%lu\n", data.start_time);
	for (int i = 0; i < num_philos; i++)
	{
		philos[i].id = i + 1;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % num_philos];
		pthread_create(&thread_id[i], NULL, routine, &philos[i]);
	}
	for (int i = 0; i < num_philos; i++)
	{
		pthread_join(thread_id[i], NULL);
	}
	for (int i = 0; i < num_philos; i++)
	{
		pthread_mutex_destroy(&(forks[i].is_lock));
	}
	return (0);
}
