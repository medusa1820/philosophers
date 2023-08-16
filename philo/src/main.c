/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:58:30 by musenov           #+#    #+#             */
/*   Updated: 2023/08/13 22:32:21 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		exit_wrong_nr_params();
	init_data(argc, argv, &data);
	
	return (0);
}

	/*
	printf("data.nr_of_philos: %d\n", data.nr_of_philos);
	printf("data.time_to_die: %d\n", data.time_to_die);
	printf("data.time_to_eat: %d\n", data.time_to_eat);
	printf("data.time_to_sleep: %d\n", data.time_to_sleep);
	printf("data.nr_must_eat: %d\n", data.nr_must_eat);
	*/
