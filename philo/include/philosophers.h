/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:58:53 by musenov           #+#    #+#             */
/*   Updated: 2023/08/09 22:16:38 by musenov          ###   ########.fr       */
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
	int				num_ph;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				num_must_eat;
	long int		begin_time;
}	t_data;

typedef struct s_philo
{
	int				num;
	int				count_eat;
	int				*died;
	int				flag;
	int				last_eat;
	int				eat_all;
	pthread_t		*th;
	pthread_mutex_t	*fork;
	pthread_mutex_t	message;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data			d_dinner;
}	t_philo;



// main.c

int		main(void);

// parser.c

int		function_test(int a, int b);


#endif
