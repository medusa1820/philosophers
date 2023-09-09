/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:18:16 by musenov           #+#    #+#             */
/*   Updated: 2023/09/09 18:35:30 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/////////////////////////////// must be reprogrammed

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

/*
uint64_t	get_start_time(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_start_time);
	time = data->start_time;
	pthread_mutex_unlock(&data->mut_start_time);
	return (time);
}
*/

void	print_schedule(t_philo *philo, char *msg)
{
	uint64_t	time;

	// time = get_time() - get_start_time(philo->data);
	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->mutex_printf);
	printf("%llu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex_printf);
}

/////////////////////////////////////////////////////////////////////

void	philo_dropped_forks(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
	{
		pthread_mutex_unlock(philo->forks[i].mutex_fork);
		pthread_mutex_unlock(philo->forks[i - 1].mutex_fork);
	}
	else
	{
		i = philo->data->nr_of_philos - 1;
		pthread_mutex_unlock(philo->forks[i].mutex_fork);
		pthread_mutex_unlock(philo->forks[0].mutex_fork);
	}
}





/////////////////////////////////////////////////////////////////////




void	set_philo_status(t_philo_status status, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_status);
	if (philo->status != DEAD)
		philo->status = status;
	pthread_mutex_unlock(&philo->mutex_status);
}




//////////////////////////////////////////////////////////////////////





void	drop_first_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i != 0)
		pthread_mutex_unlock(philo->forks[i - 1].mutex_fork);
	else
		pthread_mutex_unlock(philo->forks[0].mutex_fork);
}

bool	philo_took_second_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	// if (philo_died(philo) || get_philo_state(philo) == DEAD)
	// 	return (false);
	if (i != 0)
		pthread_mutex_lock(philo->forks[i].mutex_fork);
	else
	{
		i = philo->data->nr_of_philos - 1;
		pthread_mutex_lock(philo->forks[i].mutex_fork);
	}
	print_schedule(philo, "has taken the second fork");
	return (true);
}

bool	philo_took_first_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	// if (philo_died(philo) || get_philo_state(philo) == DEAD)
	// 	return (false);
	if (i != 0)
		pthread_mutex_lock(philo->forks[i - 1].mutex_fork);
	else
		pthread_mutex_lock(philo->forks[0].mutex_fork);
	print_schedule(philo, "has taken the first fork");
	return (true);
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

bool	philosopher_is(char *action, t_philo *philo)
{
	if (*action == "EATING")
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
	else if (*action == "SLEEPING")
	{
		set_philo_status(ALIVE, philo);
		print_schedule(philo, "is sleeping");
		my_sleep(philo->data->time_to_sleep);
		return (true);
	}
	else if (*action == "THINKING")
	{
		set_philo_status(ALIVE, philo);
		print_schedule(philo, "is thinking");
		my_sleep(philo->data->time_to_think);
		return (true);
	}
}


/*
This routine will be executed simultaneously by all threads, therefore it
includes checks for if the philo is still alive
*/

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (check_if(philo->is_alive))
	{
		if (philosopher_is("EATING", philo))
			break ;
		if (philosopher_is("SLEEPING", philo))
			break ;
		if (philosopher_is("THINKING", philo))
			break ;
	}
	return (0);
}

void	*routine_check_if_philo(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	printf("int a = %d\n", philo->a);
	return (0);
}

void	spawn_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_of_philos)
		pthread_create(&data->philo[i++].thread_philo, NULL, \
						&routine, &data->philo[i]);
	pthread_create(&data->thread_check_if_philo, NULL, \
						&routine_check_if_philo, &data->philo[i]);
}











//////////////////////////////////////////////////////////









/*







void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *) philo_p;
	update_last_meal_time(philo);
	while (get_philo_state(philo) != DEAD)
	{
		if (eat(philo) != 0)
			break ;
		if (get_philo_state(philo) == DEAD)
			break ;
		if (ft_sleep(philo) != 0)
			break ;
		if (get_philo_state(philo) == DEAD)
			break ;
		if (think(philo) != 0)
			break ;
	}
	return (NULL);
}





int	take_fork(t_philo *philo)
{
	if (philo_died(philo) || get_philo_state(philo) == DEAD)
		return (1);
	pthread_mutex_lock(philo->left_f);
	print_msg(philo->data, philo->id, TAKE_FORKS);
	return (0);
}




void	drop_left_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
}

void	drop_right_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_f);
}

int	take_left_fork(t_philo *philo)
{
	if (philo_died(philo) || get_philo_state(philo) == DEAD)
		return (1);
	pthread_mutex_lock(philo->left_f);
	print_msg(philo->data, philo->id, TAKE_FORKS);
	return (0);
}



int	take_right_fork(t_philo *philo)
{
	if (philo_died(philo) || get_philo_state(philo) == DEAD)
		return (1);
	pthread_mutex_lock(philo->right_f);
	print_msg(philo->data, philo->id, TAKE_FORKS);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (get_nb_philos(philo->data) == 1)
		return (handle_1_philo(philo));
	if (philo->id % 2 == 0)
	{
		if (take_right_fork(philo) != 0)
			return (1);
		if (take_left_fork(philo) != 0)
		{
			drop_right_fork(philo);
			return (1);
		}
	}
	else
	{
		if (take_left_fork(philo) != 0)
			return (1);
		if (take_right_fork(philo) != 0)
		{
			drop_left_fork(philo);
			return (1);
		}
	}
	return (0);
}





int	eat(t_philo *philo)
{
	if (take_forks(philo) != 0)
		return (1);
	set_philo_state(philo, EATING);
	print_msg(philo->data, philo->id, EAT);
	update_last_meal_time(philo);
	sleep_for_eating(philo);
	update_nb_meals_had(philo);
	drop_forks(philo);
	return (0);
}






*/







//////////////////////////////////////////////////////////





