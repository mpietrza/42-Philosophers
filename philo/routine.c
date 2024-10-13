/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:34:56 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/13 13:33:05 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo_routine(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	while (1)
	{
		ft_eat(p);
		if (ft_get_val_locked(p->w->waiter_lock, &p->w->state) != SERVING)
			break ;
		ft_sleep(p);
		ft_think(p);
	}
	return (ptr);
}
