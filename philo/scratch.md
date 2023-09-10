#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_fork
{
	t_data			*data;
	t_philo			*philo;
	pthread_mutex_t	mutex_fork;
}	t_fork;

typedef enum e_philo_is
{
	ALIVE,
	DEAD,
	FULL
}	t_philo_status;

typedef struct s_philo
{
	t_data			*data;
	t_fork			*forks;
	pthread_t		thread_philo;
	int				id;
	t_philo_status	status;
	pthread_mutex_t	mutex_status;
	int				nr_has_eaten;
	int				a;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	t_fork			*forks;
	int				nr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nr_must_eat;
	uint64_t		start_time;
	pthread_t		thread_check_philos_alive;
	pthread_mutex_t	mutex_printf;
}	t_data;

// main.c

int			main(int argc, char **argv);
void		spawn_threads(t_data *data);
bool		join_threads(t_data *data);
void		print_t_data(t_data data);

// init_data.c

void		init_data(int argc, char **argv, t_data *data);
void		parse_input(int argc, char **argv, t_data *data);
void		init_mutexes(t_data *data);

// utils.c

void		exit_wrong_nr_params(void);
void		free_data(t_data data);
void		print_schedule(t_philo *philo, char *msg);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);

// routines.c

void		*routine_philo(void *ph);
void		*routine_check_philos_alive(void *ph);

// routine_funcs0.c

bool		philo_alive(t_philo *philo);
bool		philosopher_is(char *action, t_philo *philo);
bool		philo_has_taken_forks(t_philo *philo);
bool		philo_took_first_fork(t_philo *philo);
bool		philo_took_second_fork(t_philo *philo);

// routine_funcs1.c

void		drop_first_fork(t_philo *philo);
void		set_philo_status(t_philo_status status, t_philo *philo);
void		philo_dropped_forks(t_philo *philo);

// time.c

void		my_sleep(int ms);
u_int64_t	get_time(void);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		exit_wrong_nr_params();
	init_data(argc, argv, &data);
	spawn_threads(&data);
	if (!join_threads(&data))
		print_t_data(data);
	// free_data(data);
	return (0);
}

void	print_t_data(t_data data)
{
	printf("data.nr_of_philos: %d\n", data.nr_of_philos);
	printf("data.time_to_die: %d\n", data.time_to_die);
	printf("data.time_to_eat: %d\n", data.time_to_eat);
	printf("data.time_to_sleep: %d\n", data.time_to_sleep);
	printf("data.nr_must_eat: %d\n", data.nr_must_eat);
}

void	spawn_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_of_philos)
	{
		pthread_create(&data->philo[i].thread_philo, NULL, \
						&routine_philo, &data->philo[i]);
		i++;
	}
	pthread_create(&data->thread_check_philos_alive, NULL, \
						&routine_check_philos_alive, &data->philo[3]);
}

bool	join_threads(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_join(data->thread_check_philos_alive, NULL))
		return (false);
	while (++i < data->nr_of_philos)
	{
		if (pthread_join(data->philo[i].thread_philo, NULL))
			return (false);
	}
	return (true);
}

bool	philo_alive(t_philo *philo)
{
	return (philo->status == ALIVE);
}

bool	philosopher_is(char *action, t_philo *philo)
{
	if (ft_strncmp(action, "EATING", 6) == 0)
	{
		if (philo_has_taken_forks(philo))
		{
			set_philo_status(ALIVE, philo);
			my_sleep(philo->data->time_to_eat);
			philo->nr_has_eaten += 1;
			philo_dropped_forks(philo);
			return (true);
		}
		else
			return (false);
	}
	else if (ft_strncmp(action, "SLEEPING", 8) == 0)
	{
		set_philo_status(ALIVE, philo);
		print_schedule(philo, "is sleeping");
		my_sleep(philo->data->time_to_sleep);
		return (true);
	}
	else if (ft_strncmp(action, "THINKING", 8) == 0)
	{
		set_philo_status(ALIVE, philo);
		print_schedule(philo, "is thinking");
		return (true);
	}
	else
		return (false);
}

bool	philo_has_taken_forks(t_philo *philo)
{
	if (philo_took_first_fork(philo))
	{
		if (philo_took_second_fork(philo))
		{
			print_schedule(philo, "is eating");
			return (true);
		}
		else
		{
			drop_first_fork(philo);
			return (false);
		}
	}
	return (false);
}

bool	philo_took_first_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
		pthread_mutex_lock(&philo->forks[i - 1].mutex_fork);
	else
		pthread_mutex_lock(&philo->forks[0].mutex_fork);
	print_schedule(philo, "has taken the first fork");
	return (true);
}

bool	philo_took_second_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
		pthread_mutex_lock(&philo->forks[i].mutex_fork);
	else
	{
		i = philo->data->nr_of_philos - 1;
		pthread_mutex_lock(&philo->forks[i].mutex_fork);
	}
	print_schedule(philo, "has taken the second fork");
	return (true);
}

void	drop_first_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
		pthread_mutex_unlock(&philo->forks[i - 1].mutex_fork);
	else
		pthread_mutex_unlock(&philo->forks[0].mutex_fork);
}

void	set_philo_status(t_philo_status status, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_status);
	if (philo->status != DEAD)
		philo->status = status;
	pthread_mutex_unlock(&philo->mutex_status);
}

void	philo_dropped_forks(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
	{
		pthread_mutex_unlock(&philo->forks[i].mutex_fork);
		pthread_mutex_unlock(&philo->forks[i - 1].mutex_fork);
	}
	else
	{
		i = philo->data->nr_of_philos - 1;
		pthread_mutex_unlock(&philo->forks[i].mutex_fork);
		pthread_mutex_unlock(&philo->forks[0].mutex_fork);
	}
}
