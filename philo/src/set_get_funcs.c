/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:49:54 by musenov           #+#    #+#             */
/*   Updated: 2024/01/03 19:32:34 by musenov          ###   ########.fr       */
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

void	set_philo_full(t_philo *philo)
{
	philo->full = true;
}

t_philo_status	get_philo_status(t_philo *philo)
{
	t_philo_status	status;

	pthread_mutex_lock(&philo->mutex_status);
	status = philo->status;
	pthread_mutex_unlock(&philo->mutex_status);
	return (status);
}

bool	ask_philo_full(t_philo *philo)
{
	return (philo->full);
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

/* 
void	free_data(t_data *data)
{
	int	i;
	int	nb_philos;

	nb_philos = get_nb_philos(data);
	i = -1;
	while (++i < nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mut_state);
		pthread_mutex_destroy(&data->philos[i].mut_nb_meals_had);
		pthread_mutex_destroy(&data->philos[i].mut_last_eat_time);
	}
	pthread_mutex_destroy(&data->mut_die_t);
	pthread_mutex_destroy(&data->mut_eat_t);
	pthread_mutex_destroy(&data->mut_sleep_t);
	pthread_mutex_destroy(&data->mut_nb_philos);
	pthread_mutex_destroy(&data->mut_print);
	pthread_mutex_destroy(&data->mut_keep_iter);
	pthread_mutex_destroy(&data->mut_start_time);
	free(data->philo_ths);
	free(data->philos);
	free(data->forks);
}
*/
