/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:58:53 by musenov           #+#    #+#             */
/*   Updated: 2023/08/12 14:06:13 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int		nr_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nr_must_eat;
}	t_data;

// main.c

int		main(int argc, char **argv);

// parser.c

void	init_data(int argc, char **argv, t_data *data);
int		ft_atoi(const char *str);

// utils.c

void	exit_wrong_nr_params(void);

#endif
