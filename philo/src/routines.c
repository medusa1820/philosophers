/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:18:16 by musenov           #+#    #+#             */
/*   Updated: 2023/12/27 18:50:23 by musenov          ###   ########.fr       */
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

void	*routine_philo(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
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
}

void	*routine_check_philos_alive(void *data_struct)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_struct;
	while (1)
	{
		i = 0;
		while (i < data->nr_of_philos)
		{
			if ((get_time() - get_last_eat_time(&data->philo[i])) > \
				data->time_to_die && \
				get_philo_status(&data->philo[i]) != EATING)
			{
				print_schedule(&data->philo[i], "died");
				i = 0;
				while (i < data->nr_of_philos)
					set_philo_status(DEAD, &data->philo[i++]);
				return (NULL);
			}
			i++;
			// my_sleep(10);
		}
		// my_sleep(10);
	}
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
