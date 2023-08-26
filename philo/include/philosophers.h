/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:58:53 by musenov           #+#    #+#             */
/*   Updated: 2023/08/26 16:31:43 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_forks
{
	bool			fork;
	pthread_mutex_t	mutex_fork;
}	t_fork;

typedef struct s_philos
{
	pthread_t		thread_philo;
	int				a;
}	t_philo;

typedef struct s_data
{
	int			nr_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nr_must_eat;
	t_philo		*philo;
	t_fork		*fork;
}	t_data;

// main.c

int		main(int argc, char **argv);
void	print_t_data(t_data data);

// parser.c

void	init_data(int argc, char **argv, t_data *data);
int		ft_atoi(const char *str);

// utils.c

void	exit_wrong_nr_params(void);
void	free_data(t_data data);

// spawn_threads.c

void	spawn_threads(t_data *data);
void	*routine(void *ph);

#endif
