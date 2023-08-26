typedef struct s_data
{
	int			nr_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nr_must_eat;
	t_philos	*philos;
	t_forks		forks;
}	t_data;

typedef struct s_forks
{
	bool			fork;
	pthread_mutex_t	mutex_fork;
}	t_forks;

typedef struct s_philos
{
	pthread_t		thread_philo;
}	t_philos;

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		exit_wrong_nr_params();
	init_data(argc, argv, &data);
	// spawn_threads();
	// print_t_data(data);
	return (0);
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
	data->philos = malloc(sizeof(data->philos) * data->nr_of_philos);
	
}

