/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:50:42 by musenov           #+#    #+#             */
/*   Updated: 2024/01/02 17:50:41 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	wrong_nr_params(void)
{
	printf("wrong number of parameters\n");
	return (EXIT_FAILURE);
}

void	destroy_and_free(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nr_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i].mutex_fork);
		pthread_mutex_destroy(&data->philo[i].mutex_status);
		pthread_mutex_destroy(&data->philo[i].mutex_last_eat_time);
		pthread_mutex_destroy(&data->philo[i].mutex_nr_has_eaten);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_printf);
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
}

void	print_schedule(t_philo *philo, char *msg)
{
	uint64_t	time;

	time = get_time() - philo->data_from_philo->start_time;
	pthread_mutex_lock(&philo->data_from_philo->mutex_printf);
	// printf("\033[43mThis text will have a yellow background.\033[0m\n");
	// "\033[0;31mdied\033[0m"
	printf("%llu %d %s\n", time, philo->id, msg);
	// printf("\033[43m%llu %d %s\033[43m\n", time, philo->id, msg);
	// printf("%lu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data_from_philo->mutex_printf);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (*(s1 + i) == *(s2 + i) && *(s1 + i) != '\0')
	{
		if (i < n - 1)
			i++;
		else
			return (0);
	}
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	output;

	i = 0;
	sign = 1;
	while ((*(str + i) >= 9 && *(str + i) <= 13) || *(str + i) == ' ')
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	output = 0;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		output = output * 10 + (*(str + i) - '0');
		if (output < 0 && sign == 1)
			return (-1);
		if (output < 0 && sign == -1 && output != -2147483648)
			return (0);
		i++;
	}
	return (output * sign);
}
