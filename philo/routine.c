/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:50:21 by mpietrza          #+#    #+#             */
/*   Updated: 2024/05/27 17:02:54 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_dead(t_data *d)
{
	int		i;
	long	crnt_tm;

	i = 0;
	while (i < d->nbr_of_philos)
	{
		crnt_tm = crnt_tm() - d->s_time;
		if (crnt_tm - d->philo[i].last_meal > d->tm_t_die)
		{
			if (d->is_smltn_on == true)
			{
				d->is_smltn_on = false;
				printf("%ld %d has died\n", crnt_tm, i);
			}
			return (true);
		}	
		i++;
	}
	return (false);
}

bool	routine(t_data *d, t_mutex *m)
{
	int	i;

	pthread_mutex_lock(&((t_mutex *)m)->mutex_i);
	i = d->id - 1;
	d->id++;
	pthread_mutex_unlock(&((t_mutex *)m)->mutex_i);

	if (i % 2 == 0)
		ft_usleep(d->tm_t_eat / 2);//!?
	while (d->is_smltn_on == true || is_philo_dead == false)
	{
		pthread_mutex_lock(&((t_mutex *)m)->mutex_fork);
		ft_take_fork((t_data *)d, i);
		pthread_mutex_unlock(&((t_mutex *)m->mutex_fork);
				ft
	}

}

void	*philo_routine(void *f)
{
}
