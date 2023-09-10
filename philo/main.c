/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:58:30 by musenov           #+#    #+#             */
/*   Updated: 2023/09/10 21:13:40 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	// while (++i < data->nr_of_philos)
	// {
	// 	if (pthread_join(data->philo[i].thread_philo, NULL))
	// 		return (false);
	// }
	return (true);
}






/*
int	join_threads(t_data *data)
{
	int	i;
	int	nb_philos;

	nb_philos = get_nb_philos(data);
	i = -1;
	if (pthread_join(data->monit_all_alive, NULL))
		return (1);
	if (nb_meals_option(data) == true
		&& pthread_join(data->monit_all_full, NULL))
		return (1);
	while (++i < nb_philos)
	{
		if (pthread_join(data->philo_ths[i], NULL))
			return (1);
	}
	return (0);
}
*/
