/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:18:16 by musenov           #+#    #+#             */
/*   Updated: 2024/01/04 00:36:34 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*

This routine will be executed simultaneously by all threads thread_philo[i], 
therefore it includes checks for if the philo is still alive


	return (NULL); 

	In the end of reoutine function marks completion of execution of thread or 
	use exit(), but it will exit all program. Also pthread_exit() can be used.

*/

/* void	*routine_philo(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (1)
	{
		if (get_philo_status(philo) == DEAD)
			break ;
		philosopher_is("EATING", philo);
		if (get_philo_status(philo) == DEAD)
			break ;
		if (!philosopher_is("SLEEPING", philo))
			break ;
		if (get_philo_status(philo) == DEAD)
			break ;
		if (!philosopher_is("THINKING", philo))
			break ;
		if (get_philo_status(philo) == DEAD)
			break ;
		my_sleep(100);
	}
	return (NULL);
} */

/* void	*routine_philo(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->data_from_philo->nr_of_philos == 1)
		return (philo_took_first_fork(philo), NULL);
	while (get_philo_status(philo) != DEAD)
	{
		if (philo_has_taken_forks(philo))
		{
			if (get_philo_status(philo) == DEAD)
				return (NULL);
			print_schedule(philo, "is eating");
			set_philo_status(EATING, philo);
			my_sleep(philo->data_from_philo->time_to_eat);
			set_last_eat_time(philo);
			philo->nr_has_eaten += 1;
			philo_dropped_forks(philo);
		}
		if (get_philo_status(philo) == DEAD)
			return (NULL);
		print_schedule(philo, "is sleeping");
		set_philo_status(ALIVE, philo);
		my_sleep(philo->data_from_philo->time_to_sleep);
		if (get_philo_status(philo) == DEAD)
			return (NULL);
		print_schedule(philo, "is thinking");
		set_philo_status(ALIVE, philo);
		// my_sleep(100);
	}
	return (NULL);
} */

void	*routine_philo(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->data_from_philo->nr_of_philos == 1)
		return (philo_took_first_fork(philo), unlock_all_mutexes(philo), NULL);
	if (philo->id % 2 == 1)
		my_sleep(philo->data_from_philo->time_to_eat / 2);
	while (get_philo_status(philo) != DEAD)
	{
		if (!philo_took_first_fork(philo))
			// return (unlock_all_mutexes(philo), NULL);
			return (NULL);
		if (!philo_took_second_fork(philo))
			// return (unlock_all_mutexes(philo), NULL);
			return (NULL);
		// if (get_philo_status(philo) == DEAD)
		print_schedule(philo, "is eating");
		philo->nr_has_eaten += 1;
		set_last_eat_time(philo);
		set_philo_status(EATING, philo);
		if (stop_iterating(philo->data_from_philo))
			// return (unlock_all_mutexes(philo), NULL);
			return (NULL);
		my_sleep(philo->data_from_philo->time_to_eat);
		// print_schedule(philo, "dropped both forks");
		philo_dropped_forks(philo);
		// if (get_philo_status(philo) == DEAD)
		if (stop_iterating(philo->data_from_philo))
			// return (unlock_all_mutexes(philo), NULL);
			return (NULL);
		print_schedule(philo, "is sleeping");
		set_philo_status(ALIVE, philo);
		my_sleep(philo->data_from_philo->time_to_sleep);
		// if (get_philo_status(philo) == DEAD)
		if (stop_iterating(philo->data_from_philo))
			// return (unlock_all_mutexes(philo), NULL);
			return (NULL);
		print_schedule(philo, "is thinking");
		set_philo_status(ALIVE, philo);
		my_sleep((philo->data_from_philo->time_to_die - get_time() + philo->last_eat_time) * 7 / 10);
	}
	return (NULL);
}

void	unlock_all_mutexes(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->data_from_philo->nr_of_philos)
	{
		pthread_mutex_unlock(&philo->forks_from_philo[i].mutex_fork);
		i++;
	}
}

void	*routine_check_philos_alive(void *data_struct)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_struct;
	i = 0;
	while (1)
	{
		if (stop_iterating(data))
			return (NULL);
		if ((get_time() - get_last_eat_time(&data->philo[i])) > \
			data->time_to_die && \
			get_philo_status(&data->philo[i]) != EATING)
		{
			print_schedule(&data->philo[i], "died");
			// i = 0;
			// while (i < data->nr_of_philos)
			// 	set_philo_status(DEAD, &data->philo[i++]);
			set_stop_iterating(data);
			return (NULL);
		}
		i++;
		if (i == data->nr_of_philos)
			i = 0;
		usleep(1000);
	}
}

bool	stop_iterating(t_data *data)
{
	bool	stop_iterating;

	pthread_mutex_lock(&data->mutex_stop_iterating);
	stop_iterating = data->stop_iterating;
	pthread_mutex_unlock(&data->mutex_stop_iterating);
	return (stop_iterating);
}

/* 
void	*all_alive_routine(void *data_p)
{
	int		i;
	int		nb_philos;
	t_data	*data;
	t_philo	*philos;

	data = (t_data *)data_p;
	philos = data->philos;
	nb_philos = get_nb_philos(data);
	i = -1;
	while (++i < nb_philos && get_keep_iter(data))
	{
		if (philo_died(&philos[i]) && get_keep_iter(data))
		{
			print_msg(data, philos[i].id, DIED);
			set_keep_iterating(data, false);
			notify_all_philos(data);
			break ;
		}
		if (i == nb_philos - 1)
			i = -1;
		usleep(1000);
	}
	return (NULL);
}
*/

void	*routine_check_philos_full(void *data_struct)
{
	t_data	*data;
	int		i;
	int		nr_philos_full;

	data = (t_data *)data_struct;
	i = 0;
	nr_philos_full = 0;
	while (1)
	{
		if (stop_iterating(data))
			return (NULL);
		if (data->philo[i].nr_has_eaten >= data->nr_must_eat && \
			ask_philo_full(&data->philo[i]) == false)
		{
			set_philo_full(&data->philo[i]);
			nr_philos_full++;
		}
		if (nr_philos_full == data->nr_of_philos)
		{
			// i = 0;
			// while (i < data->nr_of_philos)
			// 	set_philo_status(DEAD, &data->philo[i++]);
			set_stop_iterating(data);
			return (NULL);
		}
		i++;
		if (i == data->nr_of_philos)
			i = 0;
		usleep(1000);
	}
}

void	set_stop_iterating(t_data *data)
{
	pthread_mutex_lock(&data->mutex_stop_iterating);
	data->stop_iterating = true;
	pthread_mutex_unlock(&data->mutex_stop_iterating);
}
