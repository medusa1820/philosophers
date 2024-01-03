/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:58:30 by musenov           #+#    #+#             */
/*   Updated: 2024/01/04 00:24:06 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc < 5 || argc > 6)
		return (wrong_nr_params());
	init_data(argc, argv, &data);
	spawn_threads(&data);
	while (1)
	{
		i = 0;
		while (i < data.nr_of_philos)
		{
			// if (data.philo[i].status == DEAD)
			if (get_philo_status(&data.philo[i]) == DEAD)
			{
				if (!join_threads(&data))
				{
					printf("joining threads failed\n");
					destroy_and_free(&data);
					return (EXIT_FAILURE);
				}
				destroy_and_free(&data);
				return (EXIT_SUCCESS);
			}
			i++;
		}
	}
} */

/* int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc < 5 || argc > 6)
		return (wrong_nr_params());
	init_data(argc, argv, &data);
	spawn_threads(&data);
	i = 0;
	// while (i < data.nr_of_philos)
	// printf("%llu\n", data.philo->last_eat_time);
	while (1)
	{
		if (get_philo_status(&data.philo[i]) == DEAD)
		{
			if (!join_threads(&data))
			{
				printf("joining threads failed\n");
				destroy_and_free(&data);
				return (EXIT_FAILURE);
			}
			destroy_and_free(&data);
			return (EXIT_SUCCESS);
		}
		i++;
		if (i == data.nr_of_philos)
			i = 0;
	}
} */

int	main(int argc, char **argv)
{
	t_data	data;
	// int		i;

	if (argc < 5 || argc > 6)
		return (wrong_nr_params());
	init_data(argc, argv, &data);
	spawn_threads(&data);
	// i = 0;
	// while (i < data.nr_of_philos)
	// printf("%llu\n", data.philo->last_eat_time);
	if (!join_threads(&data))
	{
		printf("joining threads failed\n");
		destroy_and_free(&data);
		return (EXIT_FAILURE);
	}
	destroy_and_free(&data);
	return (EXIT_SUCCESS);
	// while (1)
	// {
	// 	if (stop_iterating(&data))
	// 	{
	// 	}
	// 	// i++;
	// 	// if (i == data.nr_of_philos)
	// 	// 	i = 0;
	// }
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

/* int	run_threads(t_data *data)
{
	int	i;
	int	nb_of_philos;

	nb_of_philos = get_nb_philos(data);
	i = -1;
	data->start_time = get_time();
	while (++i < nb_of_philos)
	{
		if (pthread_create(&data->philo_ths[i], NULL,
				&routine, &data->philos[i]))
			return (1);
	}
	if (pthread_create(&data->monit_all_alive, NULL,
			&all_alive_routine, data))
		return (1);
	if (nb_meals_option(data) == true
		&& pthread_create(&data->monit_all_full, NULL,
			&all_full_routine, data))
		return (1);
	return (0);
} */

bool	join_threads(t_data *data)
{
	int	i;
	int	is_failed;

	i = 0;
	is_failed = true;
	if (pthread_join(data->thread_check_philos_alive, NULL))
		is_failed = false;
	if ((data->nr_must_eat != 0) && pthread_join(data->thread_check_philos_full, NULL))
		is_failed = false;
	while (i < data->nr_of_philos)
	{
		if (pthread_join(data->philo[i].thread_philo, NULL))
			is_failed = false;
		i++;
	}
	return (is_failed);
}

/* void	print_t_data(t_data data)
{
	printf("data.nr_of_philos: %d\n", data.nr_of_philos);
	printf("data.time_to_die: %d\n", data.time_to_die);
	printf("data.time_to_eat: %d\n", data.time_to_eat);
	printf("data.time_to_sleep: %d\n", data.time_to_sleep);
	printf("data.nr_must_eat: %d\n", data.nr_must_eat);
} */

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
