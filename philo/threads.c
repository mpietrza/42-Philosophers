/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:18:01 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/10 22:39:18 by milosz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"




int	ft_thread_create(t_philo **ps)
{
	pthread_t	controller;
	int			i;
	
	if (pthread_create(&controller, NULL, &ft_monitoring, (void *)ps) != 0)
		return (FALSE);	
	i = 0;
	ft_assign_time_and_start(ps);
	while (i < ps[0]->nbr_of_philos)
	{
		if (pthread_create(&ps[i]->philo, NULL, &ft_philo_routine, ps[i]) != 0)
			return (FALSE);
		i++;
	}
	if (pthread_join(controller, NULL) != 0)
		return (FALSE);	
	i = 0;
	while (i < ps[0]->nbr_of_philos)
	{
		if (pthread_join(ps[i]->philo, NULL) != 0)
			return (FALSE);
		i++;
	}

	return (TRUE);
}
