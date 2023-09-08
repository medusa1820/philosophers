/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:58:53 by musenov           #+#    #+#             */
/*   Updated: 2023/09/08 22:12:57 by musenov          ###   ########.fr       */
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

typedef struct s_fork
{
	bool			taken;
	pthread_mutex_t	*mutex_fork;
	t_philo			*philo;
	t_data			*data;
}	t_fork;

typedef enum e_philo_is
{
	ALIVE,
	DEAD,
	FULL
}	t_philo_status;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_philo;
	bool			is_alive;
	int				a;
	t_fork			*forks;
	t_data			*data;
	t_philo_status	status;
	pthread_mutex_t	mutex_status;
	int				nr_has_eaten;
}	t_philo;

typedef struct s_data
{
	int				nr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nr_must_eat;
	int				start_time;
	t_philo			*philo;
	t_fork			*forks;
	pthread_t		thread_check_if_philo;
	pthread_mutex_t	mutex_is_dead;
	pthread_mutex_t	mutex_printf;
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
void	*routine_check_if_philo(void *ph);

#endif
