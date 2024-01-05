/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:00:55 by musenov           #+#    #+#             */
/*   Updated: 2024/01/05 15:03:58 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_stop_iterating(t_data *data)
{
	pthread_mutex_lock(&data->mutex_stop_iterating);
	data->stop_iterating = true;
	pthread_mutex_unlock(&data->mutex_stop_iterating);
}

bool	stop_iterating(t_data *data)
{
	bool	stop_iterating;

	pthread_mutex_lock(&data->mutex_stop_iterating);
	stop_iterating = data->stop_iterating;
	pthread_mutex_unlock(&data->mutex_stop_iterating);
	return (stop_iterating);
}

void	set_philo_full(t_philo *philo)
{
	philo->full = true;
}

bool	ask_philo_full(t_philo *philo)
{
	return (philo->full);
}
