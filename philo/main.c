/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:58:30 by musenov           #+#    #+#             */
/*   Updated: 2024/01/04 17:51:24 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (wrong_nr_params());
	init_data(argc, argv, &data);
	spawn_threads(&data);
	if (!join_threads(&data))
	{
		printf("joining threads failed\n");
		destroy_and_free(&data);
		return (EXIT_FAILURE);
	}
	destroy_and_free(&data);
	return (EXIT_SUCCESS);
}

void	spawn_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_of_philos)
	{
		pthread_create(&data->philo[i].thread_philo, NULL, routine_philo, \
						&data->philo[i]);
		i++;
	}
	pthread_create(&data->thread_check_philos_alive, NULL, \
					routine_check_philos_alive, data);
	if (data->nr_must_eat != 0)
		pthread_create(&data->thread_check_philos_full, NULL, \
						routine_check_philos_full, data);
}

bool	join_threads(t_data *data)
{
	int	i;
	int	is_failed;

	i = 0;
	is_failed = true;
	if (pthread_join(data->thread_check_philos_alive, NULL))
		is_failed = false;
	if ((data->nr_must_eat != 0) && \
		pthread_join(data->thread_check_philos_full, NULL))
		is_failed = false;
	while (i < data->nr_of_philos)
	{
		if (pthread_join(data->philo[i].thread_philo, NULL))
			is_failed = false;
		i++;
	}
	return (is_failed);
}
