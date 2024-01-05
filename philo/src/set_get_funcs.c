/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:49:54 by musenov           #+#    #+#             */
/*   Updated: 2024/01/05 15:02:55 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_philo_status(t_philo_status status, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_status);
	if (philo->status != DEAD)
		philo->status = status;
	pthread_mutex_unlock(&philo->mutex_status);
}

t_philo_status	get_philo_status(t_philo *philo)
{
	t_philo_status	status;

	pthread_mutex_lock(&philo->mutex_status);
	status = philo->status;
	pthread_mutex_unlock(&philo->mutex_status);
	return (status);
}

void	set_last_eat_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_last_eat_time);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->mutex_last_eat_time);
}

uint64_t	get_last_eat_time(t_philo *philo)
{
	uint64_t	last_eat_time;

	pthread_mutex_lock(&philo->mutex_last_eat_time);
	last_eat_time = philo->last_eat_time;
	pthread_mutex_unlock(&philo->mutex_last_eat_time);
	return (last_eat_time);
}
