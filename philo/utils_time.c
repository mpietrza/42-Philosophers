/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:33:38 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/15 17:34:43 by milosz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	ft_crnt_tm(void)
{
	struct timeval	time;
	time_t			crnt_tm;

	if (gettimeofday(&time, NULL) == -1)
		ft_err_exit(NULL, NULL, NULL, "gettimeofday error");
	crnt_tm = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (crnt_tm);
}

int	ft_usleep(time_t millisecs)
{
	time_t	start;
	time_t	so_far;

	start = ft_crnt_tm();
	if (start == (time_t) -1)
		return (FALSE);
	while (1)
	{
		so_far = ft_crnt_tm();
		if (so_far == ((time_t) -1))
			return (FALSE);
		if (so_far - start >= millisecs)
			break ;
	}
	return (TRUE);
}
