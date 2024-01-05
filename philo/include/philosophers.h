/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:58:53 by musenov           #+#    #+#             */
/*   Updated: 2024/01/05 14:58:40 by musenov          ###   ########.fr       */
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
	t_data			*data_from_fork;
	t_philo			*philo_from_fork;
	pthread_mutex_t	mutex_fork;
}	t_fork;

typedef enum e_philo_is
{
	ALIVE,
	DEAD,
	EATING
}	t_philo_status;

typedef struct s_philo
{
	t_data			*data_from_philo;
	t_fork			*forks_from_philo;
	pthread_t		thread_philo;
	int				id;
	t_philo_status	status;
	bool			full;
	pthread_mutex_t	mutex_status;
	uint64_t		last_eat_time;
	pthread_mutex_t	mutex_last_eat_time;
	int				nr_has_eaten;
	pthread_mutex_t	mutex_nr_has_eaten;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	t_fork			*forks;
	long			nr_of_philos;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	long			nr_must_eat;
	uint64_t		start_time;
	pthread_t		thread_check_philos_alive;
	pthread_t		thread_check_philos_full;
	pthread_mutex_t	mutex_printf;
	bool			stop_iterating;
	pthread_mutex_t	mutex_stop_iterating;
}	t_data;

// main.c

int					main(int argc, char **argv);
void				spawn_threads(t_data *data);
bool				join_threads(t_data *data);

// init_data.c

bool				init_data_succeeded(int argc, char **argv, t_data *data);
bool				parse_input_succeedeed(int argc, char **argv, t_data *data);
void				init_mutexes(t_data *data);

// routine_funcs.c

bool				philo_took_first_fork(t_philo *philo);
void				philo_drop_fork(t_philo *philo);
bool				philo_took_second_fork(t_philo *philo);
void				philo_dropped_forks(t_philo *philo);

// routines.c

void				*routine_philo(void *ph);
bool				philo_is_eating(t_philo *philo);
void				*routine_check_philos_alive(void *ph);
void				*routine_check_philos_full(void *data_struct);

// set_get_funcs.c

void				set_philo_status(t_philo_status status, t_philo *philo);
t_philo_status		get_philo_status(t_philo *philo);
void				set_last_eat_time(t_philo *philo);
uint64_t			get_last_eat_time(t_philo *philo);

// time.c

void				my_sleep(int ms);
u_int64_t			get_time(void);

// utils0.c

int					wrong_nr_params(void);
void				destroy_and_free(t_data *data);
void				print_schedule(t_philo *philo, char *msg);
long				ft_atoi_philo(const char *str, bool *wrong_input);

// utils1.c

void				set_stop_iterating(t_data *data);
bool				stop_iterating(t_data *data);
bool				ask_philo_full(t_philo *philo);
void				set_philo_full(t_philo *philo);

#endif
