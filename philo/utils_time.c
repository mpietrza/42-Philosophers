/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:33:38 by mpietrza          #+#    #+#             */
/*   Updated: 2024/05/14 14:46:39 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	crnt_tm(void)
{
	struct timeval	time;
	long 			crnt_tm;

	gettimeofday(&time, NULL);
	crnt_tm = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (crnt_tm);
}

void	ft_usleep(int cndtn)
{
	long	start;
	long	elpsd_tm;
	long	rmng_tm;

	start = crnt_tm();
	while (elpsd_tm = crnt_tm() - start;
	rmng_tm = cndtn - elpsd_tm;
	if (rmng_tm > 0)
		usleep(rmng_tm * 1000);
	else
		break;
}
