/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:33:38 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/07 14:56:19 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_crnt_tm(void)
{
	struct timeval	time;
	size_t			crnt_tm;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Gettimeofday() error\n");
		return ((size_t) -1);
	}
	crnt_tm = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (crnt_tm);
}

bool	ft_usleep(size_t millisecs)
{
	size_t	start;
	size_t	so_far;

	start = ft_crnt_tm();
	if (start == (size_t) -1)
		return (false);
	while (1)
	{
		so_far = ft_crnt_tm();
		if (so_far == ((size_t) -1))
			return (false);
		if (so_far - start >= millisecs)
			break ;
		usleep(500);
	}
	return (true);
}
