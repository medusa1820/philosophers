/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:44:31 by musenov           #+#    #+#             */
/*   Updated: 2024/01/03 20:22:34 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* bool	philosopher_is(char *action, t_philo *philo)
{
	if (ft_strncmp(action, "EATING", 6) == 0)
	{
		if (philo_has_taken_forks(philo))
		{
			set_philo_status(EATING, philo);
			my_sleep(philo->data_from_philo->time_to_eat);
			set_last_eat_time(philo);
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
		my_sleep(philo->data_from_philo->time_to_sleep);
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
} */

/* bool	philosopher_is(char *action, t_philo *philo)
{
	if (ft_strncmp(action, "EATING", 6) == 0)
	{
		if (philo_has_taken_forks(philo))
		{
			if (get_philo_status(philo) == DEAD)
				return (false);
			print_schedule(philo, "is eating");
			set_philo_status(EATING, philo);
			my_sleep(philo->data_from_philo->time_to_eat);
			set_last_eat_time(philo);
			philo->nr_has_eaten += 1;
			philo_dropped_forks(philo);
		}
	}
	else if (ft_strncmp(action, "SLEEPING", 8) == 0)
	{
		if (get_philo_status(philo) == DEAD)
			return (false);
		print_schedule(philo, "is sleeping");
		set_philo_status(ALIVE, philo);
		my_sleep(philo->data_from_philo->time_to_sleep);
	}
	else
	{
		set_philo_status(ALIVE, philo);
		if (get_philo_status(philo) == DEAD)
			return (false);
		print_schedule(philo, "is thinking");
	}
	return (true);
} */

/* bool	philosopher_is(char *action, t_philo *philo)
{
	if (ft_strncmp(action, "EATING", 6) == 0)
	{
		if (philo_has_taken_forks(philo))
		{
			set_philo_status(EATING, philo);
			my_sleep(philo->data_from_philo->time_to_eat);
			set_last_eat_time(philo);
			philo->nr_has_eaten += 1;
			philo_dropped_forks(philo);
		}
	}
	else if (ft_strncmp(action, "SLEEPING", 8) == 0)
	{
		set_philo_status(ALIVE, philo);
		if (get_philo_status(philo) == DEAD)
			return (false);
		print_schedule(philo, "is sleeping");
		my_sleep(philo->data_from_philo->time_to_sleep);
	}
	else
	{
		set_philo_status(ALIVE, philo);
		if (get_philo_status(philo) == DEAD)
			return (false);
		print_schedule(philo, "is thinking");
	}
	return (true);
} */

/* bool	philo_has_taken_forks(t_philo *philo)
{
	if (philo_took_first_fork(philo))
	{
		if (philo_took_second_fork(philo))
		{
			if (get_philo_status(philo) == DEAD)
				return (false);
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
} */



/* bool	philo_has_taken_forks(t_philo *philo)
{
	if (philo_took_first_fork(philo))
	{
		if (philo_took_second_fork(philo))
		{
			return (true);
		}
		else
		{
			drop_first_fork(philo);
			return (false);
		}
	}
	return (false);
} */



/* bool	philo_took_first_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
		pthread_mutex_lock(&philo->forks_from_philo[i - 1].mutex_fork);
	else
		pthread_mutex_lock(&philo->forks_from_philo[0].mutex_fork);
	print_schedule(philo, "has taken the first fork");
	return (true);
} */

bool	philo_took_first_fork(t_philo *philo)
{
	int	i;
	int	lock_result;

	lock_result = 0;
	i = philo->id;
	if (i == 1)
		pthread_mutex_lock(&philo->forks_from_philo[0].mutex_fork);
	else if (i != philo->data_from_philo->nr_of_philos)
		pthread_mutex_lock(&philo->forks_from_philo[i - 1].mutex_fork);
	else
		pthread_mutex_lock(&philo->forks_from_philo[0].mutex_fork);
	// if (get_philo_status(philo) == DEAD)
	if (stop_iterating(philo->data_from_philo))
		return (false);
	print_schedule(philo, "has taken first fork");
	return (true);
}

/* bool	philo_took_second_fork(t_philo *philo)
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
} */

/* bool	philo_took_second_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
		pthread_mutex_lock(&philo->forks_from_philo[i].mutex_fork);
	else
	{
		i = philo->data_from_philo->nr_of_philos - 1;
		pthread_mutex_lock(&philo->forks_from_philo[i].mutex_fork);
	}
	print_schedule(philo, "has taken the second fork");
	return (true);
} */

bool	philo_took_second_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i == 1)
		pthread_mutex_lock(&philo->forks_from_philo[1].mutex_fork);
	else if (i != philo->data_from_philo->nr_of_philos)
		pthread_mutex_lock(&philo->forks_from_philo[i].mutex_fork);
	else
	{
		// i = philo->data_from_philo->nr_of_philos - 1;
		pthread_mutex_lock(&philo->forks_from_philo[i - 1].mutex_fork);
	}
	// if (get_philo_status(philo) == DEAD)
	if (stop_iterating(philo->data_from_philo))
		return (false);
	print_schedule(philo, "has taken second fork");
	return (true);
}

/* void	drop_first_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 1)
		pthread_mutex_unlock(&philo->forks_from_philo[i].mutex_fork);
	else
		pthread_mutex_unlock(&philo->forks_from_philo[0].mutex_fork);
} */

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
