/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:18:55 by musenov           #+#    #+#             */
/*   Updated: 2024/01/05 15:47:56 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*

Your `my_sleep` and `get_time` functions are implemented to provide 
time-related functionalities, specifically for creating a sleep function with 
millisecond precision and getting the current time in milliseconds.

`my_sleep`:

	- Purpose: To create a delay for a specified number of milliseconds.
	- Implementation:
	- It uses `gettimeofday` to get the current time at the start and 
	repeatedly during the loop.
	- It then calculates the elapsed time in milliseconds and compares it 
	with the desired sleep duration (`ms`).
	- The loop continues until the elapsed time is greater than or equal 
	to `ms`.
	- `usleep(100)` is used to create a small delay, preventing the while 
	loop from consuming too much CPU time.

	This function effectively creates a sleep delay, but it's worth noting 
	that `usleep` is considered obsolete in POSIX.1-2008 and could be replaced 
	with `nanosleep` or similar functions for more modern and potentially 
	more precise timing control.

	This condition in while loop creates incorrect timing due to dividing 
	by 1000 the difference "now.tv_usec - start.tv_usec". 

	while ((now.tv_sec - start.tv_sec) * 1000 + \
			(now.tv_usec - start.tv_usec) / 1000 < ms)

	This approache makes timestamps more correct

	while ((now.tv_sec - start.tv_sec) * 1000 + \
			(now.tv_usec / 1000) - (start.tv_usec / 1000) < ms)

*/

void	my_sleep(int ms)
{
	struct timeval	now;
	struct timeval	start;

	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	while ((now.tv_sec - start.tv_sec) * 1000 + \
			(now.tv_usec / 1000) - (start.tv_usec / 1000) < ms)
	{
		usleep(100);
		gettimeofday(&now, NULL);
	}
}

/*

`get_time`:

	- Purpose: To get the current time in milliseconds.
	- Implementation:
	- It uses `gettimeofday` to get the current time.
	- If `gettimeofday` returns a non-zero value, indicating an error, the 
	function returns `0`.
	- Otherwise, it calculates the time in milliseconds from the `tv_sec` 
	and `tv_usec` fields of the `timeval` structure and returns this value.

	This function is a straightforward way to get the current time in milliseconds, 
	which is useful in various timing and delay calculations in your program.

*/

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}
