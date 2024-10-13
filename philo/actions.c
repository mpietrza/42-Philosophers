/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:28 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/13 16:30:05 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_message(int msg, t_philo *p, int id)
{
	pthread_mutex_lock(p->write_lock);
	p->d->msg_time[p->d->msg_counter] = ft_crnt_tm() - *p->when_sim_started;
	p->d->msg_id[p->d->msg_counter] = id;
	p->d->msg[p->d->msg_counter] = msg;
	if (p->d->msg_counter == BUF_SIZE)
	{
		p->d->is_first_message = AFTER_BUF_SIZE;
		p->d->msg_counter = 0;
	}
	else
		p->d->msg_counter++;
	pthread_mutex_unlock(p->write_lock);
}

int	ft_sleep(t_philo *p)
{
	if (ft_get_val(p->w->waiter_lock, &p->w->state) != SERVING)
		return (FALSE);
	ft_message(SLEEPING, p, p->philo_id);
	ft_usleep(p->tm_t_sleep);
	return (TRUE);
}

int	ft_think(t_philo *p)
{
	if (ft_get_val(p->w->waiter_lock, &p->w->state) != SERVING)
		return (FALSE);
	ft_message(THINKING, p, p->philo_id);
	return (TRUE);
}

