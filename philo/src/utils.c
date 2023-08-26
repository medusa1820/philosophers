/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:50:42 by musenov           #+#    #+#             */
/*   Updated: 2023/08/26 16:31:37 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/philosophers.h"
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
	if (data.fork)
		free(data.fork);
}

/*

void	error_message(void)
{
	ft_putstr_fd("Error\n", 1);
	exit (EXIT_FAILURE);
}

void	free_2d_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free(str);
}

void	free_stack(t_node *head)
{
	t_node	*current;
	t_node	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
}

void	exit_util(t_node *head, char **input)
{
	free_stack(head);
	free_2d_array(input);
	error_message();
}

*/
