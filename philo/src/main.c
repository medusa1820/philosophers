/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:58:30 by musenov           #+#    #+#             */
/*   Updated: 2023/08/09 22:47:08 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(void)
{
	char	*str;

	str = (char *)malloc(sizeof(*str));
	printf("this is result: %d\n", function_test(1, 2));
	free(str);
	return (0);
}
