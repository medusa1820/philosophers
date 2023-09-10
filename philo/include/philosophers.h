/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:58:53 by musenov           #+#    #+#             */
/*   Updated: 2023/09/10 20:56:49 by musenov          ###   ########.fr       */
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
# include <stdint.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_fork
{
	t_data			*data;
	t_philo			*philo;
	pthread_mutex_t	mutex_fork;
}	t_fork;

typedef enum e_philo_is
{
	ALIVE,
	DEAD,
	FULL
}	t_philo_status;

typedef struct s_philo
{
	t_data			*data;
	t_fork			*forks;
	pthread_t		thread_philo;
	int				id;
	t_philo_status	status;
	pthread_mutex_t	mutex_status;
	int				nr_has_eaten;
	int				a;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	t_fork			*forks;
	int				nr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nr_must_eat;
	uint64_t		start_time;
	pthread_t		thread_check_philos_alive;
	pthread_mutex_t	mutex_printf;
}	t_data;

// main.c

int			main(int argc, char **argv);
void		spawn_threads(t_data *data);
bool		join_threads(t_data *data);
void		print_t_data(t_data data);

// init_data.c

void		init_data(int argc, char **argv, t_data *data);
void		parse_input(int argc, char **argv, t_data *data);
void		init_mutexes(t_data *data);

// utils.c

void		exit_wrong_nr_params(void);
void		free_data(t_data data);
void		print_schedule(t_philo *philo, char *msg);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);

// routines.c

void		*routine_philo(void *ph);
void		*routine_check_philos_alive(void *ph);

// routine_funcs0.c

bool		philo_alive(t_philo *philo);
bool		philosopher_is(char *action, t_philo *philo);
bool		philo_has_taken_forks(t_philo *philo);
bool		philo_took_first_fork(t_philo *philo);
bool		philo_took_second_fork(t_philo *philo);

// routine_funcs1.c

void		drop_first_fork(t_philo *philo);
void		set_philo_status(t_philo_status status, t_philo *philo);
void		philo_dropped_forks(t_philo *philo);

// time.c

void		my_sleep(int ms);
u_int64_t	get_time(void);

#endif
