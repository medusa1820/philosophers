/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_funcs0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:44:31 by musenov           #+#    #+#             */
/*   Updated: 2023/09/10 13:26:05 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_alive(t_philo *philo)
{
	return (philo->status == ALIVE);
}

bool	philosopher_is(char *action, t_philo *philo)
{
	if (ft_strncmp(action, "EATING", 6) == 0)
	{
		if (philo_has_taken_forks(philo))
		{
			set_philo_status(ALIVE, philo);
			my_sleep(philo->data->time_to_eat);
			philo->nr_has_eaten += 1;
			philo_dropped_forks(philo);
			return (true);
		}
		else
			return (false);
	}
	else if (ft_strncmp(action, "SLEEPING", 8) == 0)
	{
		set_philo_status(ALIVE, philo);
		print_schedule(philo, "is sleeping");
		my_sleep(philo->data->time_to_sleep);
		return (true);
	}
	else if (ft_strncmp(action, "THINKING", 8) == 0)
	{
		set_philo_status(ALIVE, philo);
		print_schedule(philo, "is thinking");
		return (true);
	}
	else
		return (false);
}

bool	philo_has_taken_forks(t_philo *philo)
{
	if (philo_took_first_fork(philo))
	{
		if (philo_took_second_fork(philo))
		{
			print_schedule(philo, "is eating");
			return (true);
		}
		else
		{
			drop_first_fork(philo);
			return (false);
		}
	}
	return (false);
}

bool	philo_took_first_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
		pthread_mutex_lock(&philo->forks[i - 1].mutex_fork);
	else
		pthread_mutex_lock(&philo->forks[0].mutex_fork);
	print_schedule(philo, "has taken the first fork");
	return (true);
}

bool	philo_took_second_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
		pthread_mutex_lock(&philo->forks[i].mutex_fork);
	else
	{
		i = philo->data->nr_of_philos - 1;
		pthread_mutex_lock(&philo->forks[i].mutex_fork);
	}
	print_schedule(philo, "has taken the second fork");
	return (true);
}
