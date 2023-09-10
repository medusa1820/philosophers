/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:18:16 by musenov           #+#    #+#             */
/*   Updated: 2023/09/10 21:00:38 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
This routine will be executed simultaneously by all threads, therefore it
includes checks for if the philo is still alive
*/

void	*routine_philo(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	printf("int a = %d\n", philo->a);
	while (philo_alive(philo))
	{
		if (philosopher_is("EATING", philo))
			break ;
		if (philosopher_is("SLEEPING", philo))
			break ;
		if (philosopher_is("THINKING", philo))
			break ;
	}
	return (NULL);
}

void	*routine_check_philos_alive(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	printf("int a = %d\n", philo->a);
	return (NULL);
}
