#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct s_forks
{
	bool			fork;
	pthread_mutex_t	mutex_fork;
}	t_fork;

typedef struct s_philos
{
	pthread_t		thread_philo;
	int				a;
}	t_philo;

typedef struct s_data
{
	int			nr_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nr_must_eat;
	t_philo		*philo;
	t_fork		*fork;
}	t_data;

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	output;

	i = 0;
	sign = 1;
	while ((*(str + i) >= 9 && *(str + i) <= 13) || *(str + i) == ' ')
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	output = 0;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		output = output * 10 + (*(str + i) - '0');
		if (output < 0 && sign == 1)
			return (-1);
		if (output < 0 && sign == -1 && output != -2147483648)
			return (0);
		i++;
	}
	return (output * sign);
}

void	init_data(int argc, char **argv, t_data *data)
{
	data->nr_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nr_must_eat = 0;
	if (argc == 6)
		data->nr_must_eat = ft_atoi(argv[5]);
	data->philo = malloc(sizeof(t_philo) * data->nr_of_philos);
	data->fork = malloc(sizeof(t_fork) * data->nr_of_philos);
	data->philo->a = 10;
	pthread_mutex_init(&data->fork->mutex_fork, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		exit_wrong_nr_params();
	init_data(argc, argv, &data);
//	spawn_threads(&data);
//	pthread_join(data.philo->thread_philo, NULL);
//	print_t_data(data);
//	free_data(data);
	return (0);
}
