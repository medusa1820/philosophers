/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:00:30 by musenov           #+#    #+#             */
/*   Updated: 2023/09/04 18:25:38 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/philosophers.h"
#include "philosophers.h"

void	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	data->nr_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nr_must_eat = 0;
	if (argc == 6)
		data->nr_must_eat = ft_atoi(argv[5]);
	data->philo = malloc(sizeof(t_philo) * data->nr_of_philos);
	data->fork = malloc(sizeof(t_fork) * data->nr_of_philos);
	data->philo[0].a = 10;
	i = 0;
	while (i < data->nr_of_philos)
	{
		pthread_mutex_init(&data->fork[i++].mutex_fork, NULL);
		pthread_mutex_init(&data->mutex_is_dead, NULL);
	}
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

/*

void	init_stack(char **input, struct s_2stacks *two_stacks, int *nr_nodes)
{
	t_node	*head;
	int		i;
	int		num;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (!ft_atoi_push_swap(input[i], &num))
			exit_util(head, input);
		if (is_duplicate(head, num))
			exit_util(head, input);
		add_node(&head, num);
		i++;
	}
	if (is_sorted(head))
		exit_util_sorted(head, input);
	two_stacks->stack_a = head;
	*nr_nodes = count_nodes(two_stacks->stack_a);
}

*/

/*

int	ft_atoi_philo(const char *str, int *result)
{
	int		i;
	int		sign;
	long	output;

	i = 0;
	sign = 1;
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == 0)
		return (0);
	output = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		output = (sign * (str[i++] - '0') + (output * 10));
		if (output > INT_MAX || output < INT_MIN)
			return (0);
		*result = output;
	}
	return (1);
}

*/
