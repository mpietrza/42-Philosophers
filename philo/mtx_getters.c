/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:37:45 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/15 17:35:18 by milosz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_get_val(t_mtx *lock, int *value)
{
	int	result;

	pthread_mutex_lock(lock);
	result = *value;
	pthread_mutex_unlock(lock);
	return (result);
}
time_t	ft_get_time(t_mtx *lock, time_t *value)
{
	time_t	result;

	pthread_mutex_lock(lock);
	result = *value;
	pthread_mutex_unlock(lock);
	return (result);
}

static void ft_check_which_msg(t_philo *p, size_t i)
{
	if (p->d->msg[i] == TAKEN_FORK)
		printf("\033[0;33m%ld %d has taken a fork\033[0m\n",
			p->d->msg_time[i], p->d->msg_id[i]);
	else if (p->d->msg[i] == EATING)
		printf("\033[1;33m%ld %d is eating\033[0m\n",
			p->d->msg_time[i], p->d->msg_id[i]);
	else if (p->d->msg[i] == SLEEPING)
		printf("\033[0;90m%ld %d is sleeping\033[0m\n",
			p->d->msg_time[i], p->d->msg_id[i]);
	else if (p->d->msg[i] == THINKING)
		printf("\033[0;34m%ld %d is thinking\033[0m\n",
			p->d->msg_time[i], p->d->msg_id[i]);
	else if (p->d->msg[i] == DIED)
		printf("\033[1;31m%ld %d died\033[0m\n",
			p->d->msg_time[i], p->d->msg_id[i]);
}

void	ft_get_msg_and_print(t_philo *p, size_t *msg_counter_prev)
{
	size_t i;

	if (ft_get_val(&p->d->write_lock, &p->d->is_last_message))
		return ;
	if (ft_get_val(&p->d->write_lock, &p->d->is_first_message) != FALSE)
	{
		i = 0;
		p->d->is_first_message = FALSE;
	}
	else
		i = *msg_counter_prev;
	pthread_mutex_lock(p->write_lock);
	if (p->d->msg_counter != *msg_counter_prev)
	{
		while (i < p->d->msg_counter)
		{
			ft_check_which_msg(p, i);
			i++;
		}
	}
	*msg_counter_prev = p->d->msg_counter;
	pthread_mutex_unlock(p->write_lock);
}
