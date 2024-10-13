/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:37:45 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/13 14:05:56 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_get_val_locked(t_mtx *lock, int *value)
{
	int	result;

	pthread_mutex_lock(lock);
	result = *value;
	pthread_mutex_unlock(lock);
	return (result);
}
time_t	ft_get_time_locked(t_mtx *lock, time_t *value)
{
	time_t	result;

	pthread_mutex_lock(lock);
	result = *value;
	pthread_mutex_unlock(lock);
	return (result);
}

void	ft_get_msg_and_print(t_philo *p, size_t *msg_counter_prev)
{
	int i;

	if (ft_get_val_locked(p->w->waiter_lock, &p->w->state) != SERVING 
			|| ft_get_val_locked(&p->d->write_lock, &p->d->is_last_message))
		return ;
	if (ft_get_val_locked(&p->d->write_lock, &p->d->is_first_message))
	{
		i = 0;
		p->d->is_first_message = FALSE;
	}
	else
		i = *msg_counter_prev;
	pthread_mutex_lock(p->write_lock);
	if (p->d->msg_counter != *msg_counter_prev)
	{
		while (i < (int)p->d->msg_counter)
		{
			printf("i = %d\n", i);
			if (p->d->msg[i] == TAKEN_FORK)
				printf("%ld %d has taken a fork\n", p->d->msg_time[i], p->d->msg_id[i]);
			else if (p->d->msg[i] == EATING)
				printf("%ld %d is eating\n", p->d->msg_time[i], p->d->msg_id[i]);
			else if (p->d->msg[i] == SLEEPING)
				printf("%ld %d is sleeping\n", p->d->msg_time[i], p->d->msg_id[i]);
			else if (p->d->msg[i] == THINKING)
				printf("%ld %d is thinking\n", p->d->msg_time[i], p->d->msg_id[i]);
			i++;
		}
	}
	*msg_counter_prev = p->d->msg_counter;
	pthread_mutex_unlock(p->write_lock);
}
