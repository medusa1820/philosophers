/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:44:31 by musenov           #+#    #+#             */
/*   Updated: 2024/01/04 18:04:21 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_took_first_fork(t_philo *philo)
{
	int		i;
	int		mtx;

	i = philo->id;
	if (i == 1)
		mtx = 0;
	else if (i != philo->data_from_philo->nr_of_philos)
		mtx = i - 1;
	else
		mtx = 0;
	pthread_mutex_lock(&philo->forks_from_philo[mtx].mutex_fork);
	if (stop_iterating(philo->data_from_philo))
	{
		pthread_mutex_unlock(&philo->forks_from_philo[mtx].mutex_fork);
		return (false);
	}
	print_schedule(philo, "has taken a fork");
	return (true);
}

void	philo_drop_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != philo->data_from_philo->nr_of_philos)
	{
		pthread_mutex_unlock(&philo->forks_from_philo[i - 1].mutex_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks_from_philo[0].mutex_fork);
	}
}

bool	philo_took_second_fork(t_philo *philo)
{
	int		i;
	int		mtx;

	i = philo->id;
	if (i == 1)
		mtx = 1;
	else if (i != philo->data_from_philo->nr_of_philos)
		mtx = i;
	else
	{
		mtx = i - 1;
	}
	pthread_mutex_lock(&philo->forks_from_philo[mtx].mutex_fork);
	if (stop_iterating(philo->data_from_philo))
	{
		pthread_mutex_unlock(&philo->forks_from_philo[mtx].mutex_fork);
		if (i != philo->data_from_philo->nr_of_philos)
			pthread_mutex_unlock(&philo->forks_from_philo[mtx - 1].mutex_fork);
		else
			pthread_mutex_unlock(&philo->forks_from_philo[0].mutex_fork);
		return (false);
	}
	print_schedule(philo, "has taken a fork");
	return (true);
}

void	philo_dropped_forks(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != philo->data_from_philo->nr_of_philos)
	{
		pthread_mutex_unlock(&philo->forks_from_philo[i].mutex_fork);
		pthread_mutex_unlock(&philo->forks_from_philo[i - 1].mutex_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks_from_philo[i - 1].mutex_fork);
		pthread_mutex_unlock(&philo->forks_from_philo[0].mutex_fork);
	}
}
