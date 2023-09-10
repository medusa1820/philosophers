/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:18:55 by musenov           #+#    #+#             */
/*   Updated: 2023/09/09 19:27:48 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_sleep(int ms)
{
	struct timeval	now;
	struct timeval	start;

	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	while ((now.tv_sec - start.tv_sec) * 1000 + \
			(now.tv_usec - start.tv_usec) / 1000 < ms)
	{
		usleep(100);
		gettimeofday(&now, NULL);
	}
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}
