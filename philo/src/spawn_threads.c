/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:18:16 by musenov           #+#    #+#             */
/*   Updated: 2023/08/31 18:33:45 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	spawn_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_of_philos)
		pthread_create(&data->philo[i++].thread_philo, NULL, \
						&routine, &data->philo[0]);
	pthread_create(&data->thread_check_if_philo, NULL, \
						&routine_check_if_philo, &data->philo[0]);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	printf("int a = %d\n", philo->a);
	return (0);
}

void	*routine_check_if_philo(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	printf("int a = %d\n", philo->a);
	return (0);
}
