/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:58:30 by musenov           #+#    #+#             */
/*   Updated: 2023/08/26 21:19:14 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/philosophers.h"
#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		exit_wrong_nr_params();
	init_data(argc, argv, &data);
	spawn_threads(&data);
	pthread_join(data.philo->thread_philo, NULL);
	print_t_data(data);
	free_data(data);
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
