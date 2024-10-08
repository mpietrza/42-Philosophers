/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:33:38 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/08 17:50:03 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	ft_crnt_tm(void)
{
	struct timeval	time;
	size_t			crnt_tm;

	if (gettimeofday(&time, NULL) == -1)
		ft_err_exit(NULL, NULL, "gettimeofday error", 22);
	crnt_tm = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (crnt_tm);
}

int	ft_usleep(size_t millisecs)
{
	size_t	start;
	size_t	so_far;

	start = ft_crnt_tm();
	if (start == (size_t) -1)
		return (FALSE);
	while (1)
	{
		so_far = ft_crnt_tm();
		if (so_far == ((size_t) -1))
			return (FALSE);
		if (so_far - start >= millisecs)
			break ;
	}
	return (TRUE);
}
