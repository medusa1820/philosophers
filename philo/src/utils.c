/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:50:42 by musenov           #+#    #+#             */
/*   Updated: 2023/09/10 19:08:08 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_wrong_nr_params(void)
{
	printf("wrong number of parameters\n");
	exit(1);
}

void	free_data(t_data data)
{
	if (data.philo)
		free(data.philo);
	if (data.forks)
		free(data.forks);
}

void	print_schedule(t_philo *philo, char *msg)
{
	uint64_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->mutex_printf);
	printf("%llu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex_printf);
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

