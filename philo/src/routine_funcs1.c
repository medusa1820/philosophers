/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_funcs1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:49:54 by musenov           #+#    #+#             */
/*   Updated: 2023/09/10 13:26:09 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	drop_first_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
		pthread_mutex_unlock(&philo->forks[i - 1].mutex_fork);
	else
		pthread_mutex_unlock(&philo->forks[0].mutex_fork);
}

void	set_philo_status(t_philo_status status, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_status);
	if (philo->status != DEAD)
		philo->status = status;
	pthread_mutex_unlock(&philo->mutex_status);
}

void	philo_dropped_forks(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
	{
		pthread_mutex_unlock(&philo->forks[i].mutex_fork);
		pthread_mutex_unlock(&philo->forks[i - 1].mutex_fork);
	}
	else
	{
		i = philo->data->nr_of_philos - 1;
		pthread_mutex_unlock(&philo->forks[i].mutex_fork);
		pthread_mutex_unlock(&philo->forks[0].mutex_fork);
	}
}
