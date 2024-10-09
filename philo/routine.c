/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:34:56 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/09 18:35:23 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo_routine(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	while (1)
	{
		if (ft_eat(p) == FALSE)
			break ;
		if (ft_sleep(p) == FALSE)
			break ;
		if (ft_think(p) == FALSE)
			break ;
	}
	return (ptr);
}
