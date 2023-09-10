/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:00:30 by musenov           #+#    #+#             */
/*   Updated: 2023/09/10 13:44:58 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	data->nr_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nr_must_eat = 0;
	if (argc == 6)
		data->nr_must_eat = ft_atoi(argv[5]);
	data->philo = malloc(sizeof(t_philo) * data->nr_of_philos);
	data->forks = malloc(sizeof(t_fork) * data->nr_of_philos);
	data->philo[0].a = 0;
	data->philo[1].a = 1;
	data->philo[2].a = 2;
	data->philo[3].a = 3;
	data->start_time = get_time();
	i = 0;
	while (i < data->nr_of_philos)
		pthread_mutex_init(&data->forks[i++].mutex_fork, NULL);
	while (i >= 0)
		pthread_mutex_init(&data->philo[--i].mutex_status, NULL);
	pthread_mutex_init(&data->mutex_printf, NULL);
}
