/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex_and_thread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:23:08 by mpietrza          #+#    #+#             */
/*   Updated: 2024/05/13 17:15:38 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(t_data *d, t_mutex *m)
{
	int	i;

	i = 0;
	while (i < d->nbr_of_phlsphrs)
	{
		pthread_mutex_lock(&m->mutex_last_meal);
		d->phlsphr[i].last_meal = 0;
		pthread_mutex_unlock(&m->mutex_last_meal);
		if (pthread_create(&m->thread[i], NULL, &phlsphr_routine, (void *)d) != 0) //have to check it
			return (-1);
	}
	return (0);
}
