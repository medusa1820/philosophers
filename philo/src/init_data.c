/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:00:30 by musenov           #+#    #+#             */
/*   Updated: 2024/01/04 16:42:11 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*

the problem with initialization of mutexes probably was on not initializing 
data, forks and philos in each other! the original is above, let's try to fix 
it below. Apart from that, 

Initialization of data->philo: You are correctly allocating memory for 
data->philo and initializing each t_philo structure within the loop. 
However, you need to ensure that every t_philo structure's fields are fully 
initialized. This includes initializing the mutexes and setting up the links 
to data_from_philo and forks_from_philo for each philosopher.

Initialization of data->forks: You are allocating memory for data->forks, 
but you don't have a loop to initialize each t_fork. You need to initialize 
each fork, particularly the mutex_fork. Also, if data_from_fork and 
philo_from_fork are meant to be used, they need to be initialized properly.

Linking data->philo to data: The line data->philo->data_from_philo = data; 
only sets the data_from_philo for the first philosopher. You should include 
this inside the loop where you initialize data->philo so that each 
philosopher's data_from_philo points to data.

Linking data->philo to data->forks: Similar to the above point, 
data->philo->forks_from_philo = data->forks; only links the first philosopher 
to the forks. This linking needs to happen for each philosopher inside the 
loop.

Initialization of Mutexes: The call to init_mutexes(data); should properly 
initialize all mutexes in the t_data, t_philo, and t_fork structures. Ensure 
that this function is correctly implemented.

*/

void	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	parse_input(argc, argv, data);
	data->philo = malloc(sizeof(t_philo) * data->nr_of_philos);
	data->forks = malloc(sizeof(t_fork) * data->nr_of_philos);
	while (i < data->nr_of_philos)
	{
		data->philo[i].data_from_philo = data;
		data->philo[i].forks_from_philo = data->forks;
		data->philo[i].id = i + 1;
		data->philo[i].status = ALIVE;
		data->philo[i].full = false;
		data->philo[i].nr_has_eaten = 0;
		data->philo[i].last_eat_time = get_time();
		i++;
	}
	data->start_time = get_time();
	data->stop_iterating = false;
	init_mutexes(data);
}

void	parse_input(int argc, char **argv, t_data *data)
{
	data->nr_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nr_must_eat = ft_atoi(argv[5]);
	else
		data->nr_must_eat = 0;
	//check if the inputs are numrical and non-negative
}

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_of_philos)
	{
		pthread_mutex_init(&data->forks[i].mutex_fork, NULL);
		pthread_mutex_init(&data->philo[i].mutex_status, NULL);
		pthread_mutex_init(&data->philo[i].mutex_last_eat_time, NULL);
		pthread_mutex_init(&data->philo[i].mutex_nr_has_eaten, NULL);
		i++;
	}
	pthread_mutex_init(&data->mutex_printf, NULL);
}
